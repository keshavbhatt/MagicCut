#ifndef MEDIALOADER_H
#define MEDIALOADER_H

#include <QFileDialog>
#include <QMimeDatabase>
#include <QObject>

/**
 * The MediaLoader class provides a file dialog for loading media files into a
 * QMediaPlayer object.
 */
class MediaLoader : public QObject
{
    Q_OBJECT

public:
    /**
     * Constructs a new MediaLoader object.
     *
     * @param parent The parent QObject (optional).
     */
    explicit MediaLoader(QObject *parent = nullptr);

private:
    QStringList m_mimeFilters;
    QMimeDatabase m_mimeDb;

public slots:

    /**
     * Displays a file dialog for loading media files.
     *
     * Emits the filesLoaded(QStringList &fileNames) signal when the user selects one
     * or more files.
     */
    void loadMediaFiles();

signals:
    /**
     * Emitted when a QStringList object has been loaded with the selected
     * media files.
     *
     * @param fileNames reference to the selected files.
     */
    void filesLoaded(QStringList &fileNames);
};

#endif // MEDIALOADER_H
