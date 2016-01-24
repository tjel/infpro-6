#ifndef ARCHIVEWINDOW_H
#define ARCHIVEWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class ArchiveWindow;
}

class ArchiveWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::ArchiveWindow *ui;

    explicit ArchiveWindow(QObject* parent = 0);
    ~ArchiveWindow();

signals:
    void windowClosed();
};

#endif // ARCHIVEWINDOW_H
