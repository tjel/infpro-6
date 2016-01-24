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
                    "  background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(225, 210, 110, 250), stop:1 rgba(255, 220, 70, 115));\n"
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
