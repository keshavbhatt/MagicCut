#include "mediainfoviewer.h"
#include "ui_mediainfoviewer.h"
#include <QDir>

#define MAX_TREEVIEW_EXPAND_DEPTH 2

MediaInfoViewer::MediaInfoViewer(QWidget *parent, const QString &filepath)
    : QWidget(parent)
    , ui(new Ui::MediaInfoViewer)
    , m_model(new JsonModel(this))
    , m_proxyModel(new FilterableSortFilterProxyModel())
{
    ui->setupUi(this);
    ui->fileName->setReadOnly(true);
    ui->editView->setReadOnly(true);
    ui->tabWidget->setCurrentWidget(ui->treeViewTab);

    connect(ui->searchLe, &QLineEdit::textChanged, this, &MediaInfoViewer::searchLe_textChanged);

    QString cache_path = QStandardPaths::writableLocation(QStandardPaths::CacheLocation)
                         + QDir::separator() + "Cachier" + QDir::separator() + "MediaInfo";

    // init cachier ensuring cache path
    cachier = new Cachier(cache_path.toStdString(), true);

    loadMediaInfo(filepath);
}

void MediaInfoViewer::loadMediaInfo(const QString &filePath)
{
    // set current filepath
    ui->fileName->setText(filePath);

    // load info
    MediaInfo *mediaInfo = new MediaInfo(this);
    connect(mediaInfo,
            &MediaInfo::infoReady,
            this,
            [=](const QString &filename, const QString &info) {
                ui->fileName->setText(filename);
                if (info.trimmed().simplified().isEmpty() == false) {
                    //save to cache
                    if (cachier->isInitialized()) {
                        cachier->addCache(filePath.toStdString(),
                                          info.toStdString(),
                                          Cachier::CacheOverwriteOption::OVERWRITE_CACHE);
                    }

                    // load media info data in main data model
                    m_model->setJson(info.toUtf8());

                    // bind highlighter to source editView
                    new JsonHighlighter(ui->editView->document());

                    //set source in editView
                    ui->editView->setPlainText(m_model->document().toJson());

                    // set proxyModel's source model to the main data model for filtering
                    m_proxyModel->setSourceModel(m_model);

                    // filter all columns, recursively, enable dynamiccally sorting/filtering,
                    // sort to ensure model sorted correctly after filtering
                    m_proxyModel->setFilterKeyColumn(-1);
                    m_proxyModel->setFilterRole(Qt::DisplayRole);
                    m_proxyModel->setRecursiveFilteringEnabled(true);
                    m_proxyModel->setDynamicSortFilter(true);
                    m_proxyModel->sort(0);

                    // set up a filter to only show items that contain the text searchterm
                    m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

                    // set the proxy model as the model for tree view
                    ui->treeView->setModel(m_proxyModel);

                    // set expand despth of treeview
                    ui->treeView->expandToDepth(MAX_TREEVIEW_EXPAND_DEPTH);

                    // unformly stretch headers to make items visible
                    for (int i = 0; i < ui->treeView->header()->count(); ++i) {
                        ui->treeView->header()->setSectionResizeMode(i, QHeaderView::Stretch);
                    }
                } else {
                    QMessageBox::critical(this,
                                          tr("Failed to get media information."),
                                          "Parsed information is empty!");
                }
                mediaInfo->deleteLater();
            });
    connect(mediaInfo, &MediaInfo::infoFailed, this, [=](const QString &error) {
        mediaInfo->deleteLater();
        QMessageBox::critical(this,
                              tr("Failed to get media information."),
                              QString("Parsed information is empty!<br>%1").arg(error));
    });

    if (cachier->isInitialized() && cachier->cacheExists(filePath.toStdString())) {
        Cachier::HashResult hash_result = cachier->computeHash(filePath.toStdString());
        std::string key = std::to_string(hash_result.key);
        if (!key.empty()) {
            emit mediaInfo->infoReady(filePath, QString::fromStdString(cachier->getContent(key)));
            qDebug() << "Cachier::getContent";
        } else {
            qDebug() << "MediaInfo::getInfo";
            mediaInfo->getInfo(filePath);
        }
    } else {
        qDebug() << "MediaInfo::getInfo";
        mediaInfo->getInfo(filePath);
    }
}

MediaInfoViewer::~MediaInfoViewer()
{
    if (cachier != nullptr) {
        delete cachier;
    }
    delete ui;
}

void MediaInfoViewer::searchLe_textChanged(const QString &arg1)
{
    // ensure that the regular expression is interpreted as a fixed string using QRegExp::FixedString
    m_proxyModel->setFilterRegExp(QRegExp(arg1, Qt::CaseInsensitive, QRegExp::FixedString));

    // expand all items in the filtered tree to max depth (-1) hack
    ui->treeView->expandToDepth(-1);
}
