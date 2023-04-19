#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QObject>
#include <qcustomplot.h>
#include <ecggraph.h>
#include <QMessageBox>
#include "producer.h"
#include "consumer.h"
#include "datread.h"
#include <QDebug>
#include "definition.h"
#include "ecggraph.h"
#include "slider.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void plotGraph_preview(const vector<double> &axisX, const vector<vector<double>> &axisCH);
//    QDateTime DateTime;

    void initialize_Plot();  //初始化图像
    void initializ_Slider(int length);//初始化滑块
//    void plotGraph_view(const vector<double> &axisX,const vector<vector<double>> &axisCH);

    //在ui上读取磁盘的相关参数
    QString address;
    uint offset;
    int times;
    int datanum;
    int headnum;
    int effnum;
    int idatlength;  //代表所读取的秒数
    int position; //图像显示的数据位置
    int isliderlen; //代表滑块长度
    bool sliderflag; //滑块标志位

private slots:

    void on_read_clicked();  //ui界面中读取槽函数



private:
    Ui::MainWindow *ui;

    ECGGraph *ecgGraph_preview;   //开始显示8个通道


signals:

    void readfromdisk();
    void SliderValueChange(int position);

};

#endif // MAINWINDOW_H
