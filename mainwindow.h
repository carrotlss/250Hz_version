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
    void plotGraph_preview2(const vector<double> &axisX, const vector<double> &axisCH);
//    QDateTime DateTime;

    void initialize_Plot();  //初始化图像
    void initializ_Slider(int length);//初始化滑块
//    void plotGraph_view(const vector<double> &axisX,const vector<vector<double>> &axisCH);

    //在ui上读取磁盘的相关参数 250Hz
    QString address;
    qint64 offset;
    int times;
    int datanum;
    int headnum;
    int effnum;
    int idatlength;  //代表所读取的秒数
    int position; //图像显示的数据位置
    int isliderlen; //代表滑块长度
    bool sliderflag; //滑块标志位

    //8000Hz
    QString address_2;
    qint64 offset_2;
    int times_2;
    int datanum_2;
    int headnum_2;
    int effnum_2;
    int idatlength_2;


private slots:

    void on_read_clicked();  //ui界面中读取槽函数



    void on_read_2_clicked();

private:
    Ui::MainWindow *ui;

    ECGGraph *ecgGraph_preview;   //250Hz 7个通道
    ECGGraph *ecgGraph_preview_2;   //8000Hz


signals:

    void readfromdisk();
    void readfromdisk_2();
    void SliderValueChange(int position);

};

#endif // MAINWINDOW_H
