#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "medialibrary.h"
#include "timeline.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MediaLibrary *m_mediaLibrary;
    TimeLine *m_timeLine;
};
#endif // MAINWINDOW_H
