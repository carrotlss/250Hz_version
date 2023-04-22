#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>
#include <QThread>
#include "myqueue.h"


class Consumer : public QThread
{
    Q_OBJECT
public:
    void run();
    int mode;
signals:
    void savdatnum(int);
    void consumerstopflag();

};

#endif // CONSUMER_H
