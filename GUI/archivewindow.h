#ifndef ARCHIVEWINDOW_H
#define ARCHIVEWINDOW_H

#include <QMainWindow>

namespace Ui {
class ArchiveWindow;
}

class ArchiveWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArchiveWindow(QWidget *parent = 0);
    ~ArchiveWindow();

private:
    Ui::ArchiveWindow *ui;
};

#endif // ARCHIVEWINDOW_H
