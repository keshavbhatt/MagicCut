#ifndef MEDIALIBRARY_H
#define MEDIALIBRARY_H

#include "mediainfoviewer.h"
#include "medialoader.h"
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
};

#endif // MEDIALIBRARY_H
