#include "eventfilter.h"

KeyPressFilter::KeyPressFilter(QObject* parent)
    : QObject(parent)
{
}

bool KeyPressFilter::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        int key = keyEvent->key();

        if (key == 16777220 || key == 16777221)
        {
            if (!keyEvent->modifiers().testFlag(Qt::ShiftModifier) &&
                !keyEvent->modifiers().testFlag(Qt::ControlModifier))
            {
                emit enterPressed();
                return true;
            }
        }
    }

    return QObject::eventFilter(obj, event);
}
