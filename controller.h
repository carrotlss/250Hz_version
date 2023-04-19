#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "producer.h"
#include "consumer.h"
#include "mainwindow.h"
#include "datread.h"
#include "definition.h"


class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    MainWindow *mainwindow;
    void startshow();  //窗口显示
    void startread();  //从磁盘中读取数据

    void plotGraph_preview(); //调用mainwindow里的图片显示


    int savefilenum;  //存储文件数目
    int position; //文件读取位置

public slots:
    void plotshowinit(int); //显示首张图片,并记录文件存储情况
    void plotGraph_view(int);

private:
    Producer *producer;
    Consumer *consumer;
    Datread *datread;
    vector<double> *axisX;                  //横轴
    vector<vector<double>> *axisCH;         //各个导联的值
    int idatlength;  //代表所读取的秒数
    int pos;  //读取的位置


signals:

};

#endif // CONTROLLER_H
