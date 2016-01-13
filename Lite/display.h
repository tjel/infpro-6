#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <QObject>
#include <QString>
#include <QTextStream>
#include <QDateTime>

class Display : public QObject
{
    Q_OBJECT

    static const QString DATETIMEFORMAT;

public slots:
    void print(QString, QDateTime);
};

#endif // DISPLAY_H

