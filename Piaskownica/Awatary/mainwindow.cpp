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

    QPixmap pixmap(":/avatar.png");
    QRegion exposed;

    ui->bigavatar->pixmapp.scroll(10, 10, pixmap.rect(), &exposed);//setPixmap(pix);

}

MainWindow::~MainWindow()
{
    delete ui;
}
