#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include <QDebug>
#include "chat.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Chat* c = new Chat(&w);

    w.show();

    return a.exec();
}
