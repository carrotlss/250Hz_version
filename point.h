#ifndef POINT_H
#define POINT_H
#include "definition.h"
#include <QObject>
#include "QFile"

class Point
{
public:
    explicit Point();
    int decode();    
    void push(const BYTE &b);
    int savedat(int);
    FILE *file;

private:
    BYTE m_data[BUFFER_SIZE];
    static BYTE onewrite[ONEWRITE_SIZE];
    int cur;
    static int writenum;
    static int timenum;
    static int filenum;
//    void savedatfile(int len,QString &aFilename);
};


#endif // POINT_H
