#ifndef EVENTFILTER_H
#define EVENTFILTER_H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

class KeyPressFilter : public QObject
{
    Q_OBJECT

public:
    KeyPressFilter(QObject* parent=0);

protected:
    bool eventFilter(QObject*, QEvent*);

signals:
    void enterPressed();
};

#endif // EVENTFILTER_H

