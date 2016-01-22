#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>

namespace Ui
{
    class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    Ui::ChatWidget *ui;

    explicit ChatWidget(QWidget *parent=0);
    ~ChatWidget();
};

#endif // CHATWIDGET_H
