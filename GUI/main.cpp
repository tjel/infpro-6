#include "mainwindow.h"
#include <QApplication>
#include "chat.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    Chat* c = new Chat(&w);

    w.show();

    return a.exec();
}
