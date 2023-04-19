#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>
#include "point.h"
class MyQueue : public QObject
{
    Q_OBJECT
public:
    static MyQueue& getGlobalInstance();
    int put(const Point &p);
    int get(Point *p);
    void stop();

private:
    explicit MyQueue(){};
    MyQueue(const MyQueue&)=delete;
    MyQueue& operator=(const MyQueue&)=delete;
    QMutex mtx;
    QWaitCondition bufferNotEmpty;
    QWaitCondition bufferNotFull;
    QQueue<Point> m_data;
    bool stopped=false;
signals:

};

#endif // MYQUEUE_H
