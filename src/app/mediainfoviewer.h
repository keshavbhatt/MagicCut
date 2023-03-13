#ifndef MEDIAINFOVIEWER_H
#define MEDIAINFOVIEWER_H

#include "utils.h"
#include "filterablesortfilterproxymodel.h"
#include "lib/ffprobe/MediaInfo.hpp"
#include "lib/json/jsonhighlighter.h"
#include "lib/json/jsonmodel.h"

#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QWidget>

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
};

#endif // MEDIAINFOVIEWER_H
