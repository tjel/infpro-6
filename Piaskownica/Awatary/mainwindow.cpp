#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include "chatwidget.h"
#include <QDebug>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QImage icon(100, 100, QImage.Format_RGB32);
    QImageReader reader("avatar.png");
    ui->bigavatar->setPixmap(reader);

    //QPixmap pixmap(":/avatar.png");
    //QRegion exposed;

    //ui->bigavatar->pixmapp.scroll(10, 10, pixmap.rect(), &exposed);//setPixmap(pix);

}

MainWindow::~MainWindow()
{
    delete ui;
}
