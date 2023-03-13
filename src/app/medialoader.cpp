#include "medialoader.h"

MediaLoader::MediaLoader(QObject *parent)
    : QObject{parent}
{}

void MediaLoader::loadMediaFiles()
{
    QFileDialog fileDialog;
    fileDialog.setNameFilter(tr("Media files (*.mp3 *.mp4 *.avi *.mov *.wmv)"));
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    fileDialog.setWindowTitle(tr("Load Media Files"));

    if (fileDialog.exec()) {
        QStringList fileNames = fileDialog.selectedFiles();
        emit filesLoaded(fileNames);
    }
}
