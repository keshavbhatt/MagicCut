#include "medialibrary.h"
#include "ui_medialibrary.h"
#include <QDebug>

MediaLibrary::MediaLibrary(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MediaLibrary)
    , m_mediaLoader(new MediaLoader(this))
{
    ui->setupUi(this);
    this->layout()->setContentsMargins(0, 0, 0, 0);

    // init mediaLoader
    connect(m_mediaLoader, &MediaLoader::filesLoaded, ui->mediaListWidget, &QListWidget::addItems);
    updateRemoveMediaButton();
    updateMediaInfoButton();

    // connect tool buttons
    connect(ui->addMediaPb, &QPushButton::clicked, this, &MediaLibrary::addMediaPb_clicked);
    connect(ui->removeMediaPb, &QPushButton::clicked, this, &MediaLibrary::removeMediaPb_clicked);
    connect(ui->mediaInfoPb, &QPushButton::clicked, this, &MediaLibrary::mediaInfoPb_clicked);

    // init mediamediaListWidget
    connect(ui->mediaListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChanged()));
}

void MediaLibrary::addMediaPb_clicked()
{
    m_mediaLoader->loadMediaFiles();
}

void MediaLibrary::removeMediaPb_clicked()
{
    QListWidgetItem *selectedItem = ui->mediaListWidget->currentItem();
    if (selectedItem != nullptr) {
        // only remove the item if it is selected
        delete ui->mediaListWidget->takeItem(ui->mediaListWidget->row(selectedItem));
    }
    updateRemoveMediaButton();
}

void MediaLibrary::mediaInfoPb_clicked()
{
    QListWidgetItem *selectedItem = ui->mediaListWidget->currentItem();
    if (selectedItem != nullptr) {
        m_mediaInfoViewer = new MediaInfoViewer(this, selectedItem->text().trimmed());
        m_mediaInfoViewer->setWindowTitle(QApplication::applicationName() + " | "
                                          + "Media Information");
        m_mediaInfoViewer->setWindowFlags(Qt::Window);
        m_mediaInfoViewer->setAttribute(Qt::WA_DeleteOnClose);
        m_mediaInfoViewer->show();
    }
}

void MediaLibrary::itemSelectionChanged()
{
    updateRemoveMediaButton();

    updateMediaInfoButton();
}

void MediaLibrary::updateRemoveMediaButton()
{
    ui->removeMediaPb->setEnabled(ui->mediaListWidget->count() > 0);
    QListWidgetItem *selectedItem = ui->mediaListWidget->currentItem();
    ui->removeMediaPb->setEnabled(selectedItem != nullptr);
}

void MediaLibrary::updateMediaInfoButton()
{
    ui->mediaInfoPb->setEnabled(ui->mediaListWidget->count() > 0);
    QListWidgetItem *selectedItem = ui->mediaListWidget->currentItem();
    ui->mediaInfoPb->setEnabled(selectedItem != nullptr);
}

MediaLibrary::~MediaLibrary()
{
    delete ui;
}