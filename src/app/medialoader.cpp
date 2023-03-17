#include "medialoader.h"

MediaLoader::MediaLoader(QObject *parent)
    : QObject{parent}
{
    // init mime filter list
    auto all_mime_types = m_mimeDb.allMimeTypes();
    for (const QMimeType &mimeType : qAsConst(all_mime_types)) {
        QString type = mimeType.name();
        if (type.startsWith("audio/") || type.startsWith("video/")) {
            // filterout playlist types
            if (type.contains("playlist") == false) {
                m_mimeFilters << type;
            }
        }
    }
}

void MediaLoader::loadMediaFiles()
{
    QFileDialog fileDialog;
    fileDialog.setMimeTypeFilters(m_mimeFilters);
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    fileDialog.setWindowTitle(tr("Load Media Files"));

    if (fileDialog.exec()) {
        QStringList fileNames = fileDialog.selectedFiles();
        emit filesLoaded(fileNames);
    }
}
