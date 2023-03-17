#include <QObject>
#include <QtWidgets>

class LibraryListWidget : public QListWidget
{
    Q_OBJECT
private:
    QPoint m_dragStartPosition;

public:
    LibraryListWidget(QWidget *parent = nullptr)
        : QListWidget(parent)
    {
        setSelectionMode(QAbstractItemView::SingleSelection);
        setDragEnabled(true);
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            m_dragStartPosition = event->pos();
        }

        QListWidget::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        // check if the drag distance is greater than a threshold
        if ((event->buttons() & Qt::LeftButton)
            && (event->pos() - m_dragStartPosition).manhattanLength()
                   > QApplication::startDragDistance()) {
            QListWidgetItem *item = currentItem();
            if (item) {
                QDrag *drag = new QDrag(this);
                QMimeData *mime_data = new QMimeData;
                QString file_path = item->data(Qt::UserRole).toString();
                mime_data->setUrls({ QUrl::fromLocalFile(file_path) });
                drag->setMimeData(mime_data);
                drag->exec(Qt::CopyAction);
            }
        }
        QListWidget::mouseMoveEvent(event);
    }

signals:
    void mediaDropped(const QString &file_path);
};
