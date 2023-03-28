#include <QMimeDatabase>
#include <QtWidgets>

class MediaDropWidget : public QWidget
{
    Q_OBJECT
public:
    MediaDropWidget(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setAcceptDrops(true);
    }

protected:
    void dragEnterEvent(QDragEnterEvent *event) override
    {
        if (event->mimeData()->hasUrls()) {
            auto mime_data_urls = event->mimeData()->urls();
            for (const QUrl &url : qAsConst(mime_data_urls)) {
                QString file_path = url.toLocalFile();
                QMimeType mime_type = QMimeDatabase().mimeTypeForFile(file_path);
                QString mime_name = mime_type.name();
                if ((mime_name.startsWith("audio/") || mime_name.startsWith("video/"))
                    && !mime_name.contains("playlist")) {
                    event->acceptProposedAction();
                    return;
                }
            }
        }

        event->ignore();
    }

    void dropEvent(QDropEvent *event) override
    {
        // get the dropped file path and emit fileDropped signal
        auto mime_data_urls = event->mimeData()->urls();
        for (const QUrl &url : qAsConst(mime_data_urls)) {
            QString file_path = url.toLocalFile();
            QMimeType mime_type = QMimeDatabase().mimeTypeForFile(file_path);
            QString mime_name = mime_type.name();
            if ((mime_name.startsWith("audio/") || mime_name.startsWith("video/"))
                && !mime_name.contains("playlist")) {
                emit mediaDropped(file_path);
                return;
            }
        }

        event->ignore();
    }

signals:
    void mediaDropped(const QString &file_path);
};
