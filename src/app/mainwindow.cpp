#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_mediaLibrary(new MediaLibrary(this))
    , m_timeLine(new TimeLine(this))
{
    ui->setupUi(this);

    // init mainwindow
    setWindowTitle(QApplication::applicationName());
    setWindowIcon(QIcon(":/icons/app/icon-64.png")); //FIXME provide app icon in defined location

    // add library widget
    ui->libraryTab->layout()->addWidget(m_mediaLibrary);

    //add timeline widget
    m_timeLine->setMinimumHeight(250);
    ui->timeLineTopFrame->layout()->addWidget(m_timeLine);
}

MainWindow::~MainWindow()
{
    delete ui;
}
