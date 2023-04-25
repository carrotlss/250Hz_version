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
    void startread();  //从磁盘中读取数据 250Hz
    void startread_2();

    void plotGraph_preview(); //调用mainwindow里的图片显示
    void plotGraph_preview2();


    int savefilenum;  //存储文件数目 250Hz
    int savefilenum2;  //存储文件数目 8000Hz
    int position; //文件读取位置

public slots:
    void plotshowinit(int); //显示首张图片,并记录文件存储情况
    void plotshowinit2(int);
    void plotGraph_view(int);
    void plotGraph_view2(int);

private:
    Producer *producer;
    Consumer *consumer;
    Producer *producer_2;
    Consumer *consumer_2;
    Datread *datread;
    vector<double> *axisX;                  //横轴 250Hz
    vector<vector<double>> *axisCH;         //各个导联的值 250Hz
    vector<double> *axisX2;                  //横轴 8000Hz
    vector<double> *axisCH2;         //各个导联的值 8000Hz
    int idatlength;  //代表所读取的秒数 250Hz
    int idatlength_2;  //代表所读取的秒数 250Hz
    int pos;  //读取的位置


signals:

};

#endif // CONTROLLER_H
