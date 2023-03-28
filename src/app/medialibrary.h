#ifndef MEDIALIBRARY_H
#define MEDIALIBRARY_H

#include "mediainfoviewer.h"
#include "medialoader.h"
#include "utils.h"
#include <QWidget>

namespace Ui {
class MediaLibrary;
}

class MediaLibrary : public QWidget
{
    Q_OBJECT

public:
    explicit MediaLibrary(QWidget *parent = nullptr);
    ~MediaLibrary();

private:
    Ui::MediaLibrary *ui;

    MediaLoader *m_mediaLoader;
    MediaInfoViewer *m_mediaInfoViewer;

private slots:
    void addMediaPb_clicked();

    void removeMediaPb_clicked();

    void updateRemoveMediaButton();

    void itemSelectionChanged();

    void updateMediaInfoButton();

    void mediaInfoPb_clicked();

public slots:
    /**
     * Loads files and add them to the mediaListWidget as QListWidgetItem
     *
     * @brief loadFiles
     * @param filesPath QStringList containing paths of files to be loadded
     */
    void loadFiles(QStringList &filesPath);
};

#endif // MEDIALIBRARY_H
