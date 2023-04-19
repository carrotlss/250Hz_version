#ifndef PRODUCER_H
#define PRODUCER_H

#include <QObject>
#include <QThread>
#include "myqueue.h"
class Producer : public QThread
{
    Q_OBJECT
public:
    void run();

public slots:
//    void getaddress(QString);
//    void getoffset(uint);
//    void gettimes(int);
//    void getdatnum(int);
//    void getheadnum(int);
//    void geteffnum(int);

public:
    QString address;
    uint offset;
    int times;
    int datanum;
    int headnum;
    int effnum;


signals:
    void producerstopflag();

};

#endif // PRODUCER_H
