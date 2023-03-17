#include "timeline.h"
#include "ui_timeline.h"
#include <QDebug>

TimeLine::TimeLine(QWidget *parent)
    : MediaDropWidget(parent)
    , ui(new Ui::TimeLine)
{
    ui->setupUi(this);

    connect(this, &TimeLine::fileDropped, [=](const QString &file_path) {
        qDebug() << QString("Dropped media file: %1").arg(file_path);
    });
}

TimeLine::~TimeLine()
{
    delete ui;
}
