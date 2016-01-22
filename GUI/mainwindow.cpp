#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include "chatwidget.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralWidget->setStyleSheet(
                QString::fromUtf8(
                    "QWidget#centralWidget\n"
                    "{\n"
                    "  background-color: rgba(225, 210, 110, 250);\n"
                    "}\n"));
    ui->tabs->setStyleSheet( // nie działa :[
                QString::fromUtf8(
                    "QWidget#tabs\n"
                    "{\n"
                    "  color: rgba(225, 210, 110, 150);\n"
                    "}\n"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openHistory()
{
    ArchiveWindow* archive = new ArchiveWindow(this);
    archive->show();
}
