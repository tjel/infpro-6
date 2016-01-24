#include "archivewindow.h"
#include "ui_archivewindow.h"

ArchiveWindow::ArchiveWindow(QObject* parent) :
    ui(new Ui::ArchiveWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setStyleSheet(
                QString::fromUtf8(
                    "QWidget#centralwidget\n"
                    "{\n"
                    "  background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(200, 230, 100, 245), stop:1 rgba(255, 220, 70, 115));\n"
                    "}\n"));
}

ArchiveWindow::~ArchiveWindow()
{
    delete ui;
}
