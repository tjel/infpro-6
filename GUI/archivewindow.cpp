#include "archivewindow.h"
#include "ui_archivewindow.h"

ArchiveWindow::ArchiveWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArchiveWindow)
{
    ui->setupUi(this);
}

ArchiveWindow::~ArchiveWindow()
{
    delete ui;
}
