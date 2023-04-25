#ifndef DATREAD_H
#define DATREAD_H

#include <QFile>
#include "definition.h"
#include <stdio.h>
#include <QDebug>
#include <vector>
#include <QThread>
//#include <QRunnable>
using namespace std;

class Datread :public QThread
{
    Q_OBJECT
public:
    QString filepath;   //文件路径
    vector<double> *axisX;  //横轴
    vector<vector<double>> *axisCH;  //各个导联的值 250Hz
    vector<double> *axisCH2;  //各个导联的值 8000Hz
    int pos;  //数据在文件中的偏移位置
    int len;  //读取数据
    int mode;

public:
    explicit Datread();
    void byteread_pos(const QString &path,int pos,int len,vector<double> &axisX,vector<vector<double> > &axisCH);
    void byteread_pos2(const QString &path,int pos,int len,vector<double> &axisX,vector<double>  &axisCH2);
    void run() ;    //QThread的虚函数

signals:
    void datready();

};

#endif // DATREAD_H
