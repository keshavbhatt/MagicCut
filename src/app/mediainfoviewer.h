#ifndef MEDIAINFOVIEWER_H
#define MEDIAINFOVIEWER_H

#include "externals/Cachier/cachier.h"
#include "filterablesortfilterproxymodel.h"
#include "lib/ffprobe/MediaInfo.hpp"
#include "lib/json/jsonhighlighter.h"
#include "lib/json/jsonmodel.h"
#include "utils.h"

#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QWidget>
#include <QStandardPaths>

class JsonModel;

namespace Ui {
class MediaInfoViewer;
}

class MediaInfoViewer : public QWidget
{
    Q_OBJECT

public:
    explicit MediaInfoViewer(QWidget *parent = nullptr, const QString &filepath = "");
    ~MediaInfoViewer();

private slots:
    void loadMediaInfo(const QString &filePath);
    void searchLe_textChanged(const QString &arg1);

private:
    Ui::MediaInfoViewer *ui;
    JsonModel *m_model;
    FilterableSortFilterProxyModel *m_proxyModel;
    int m_modelMaxDepth;
    Cachier *cachier;
};

#endif // MEDIAINFOVIEWER_H
