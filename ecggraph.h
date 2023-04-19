#ifndef ECGGRAPH_H
#define ECGGRAPH_H
// @brief: 画曲线图
// @birth: created by BR on 20221208

#include <QObject>
#include <QTime>
#include <QAction>
#include <QMenu>
#include <QColor>
#include <QString>
#include <QPen>
#include <QBrush>
#include <vector>
#include <qcustomplot.h>
using namespace std;
class ECGGraph : public QObject
{
    Q_OBJECT
public:
    explicit ECGGraph(QCustomPlot *customPlot);
    ~ECGGraph();

private:
    double count = 0;
public:
    QPen pen = QPen(QColor(Qt::blue));
    int width;
    int height;
protected:
    QCustomPlot *customGraphPlot;
    QCPGraph *graph;                                                                //曲线图

public:
    void setFixedSize(int width, int height);                                       //设置为固定的大小
    void setPen(QPen pen);                                                          //设置画笔的颜色

    void setxAxisRange(double start,double end);                                     //设置X轴的范围
    void setyAxisRange(double start,double end);                                    //设置Y轴的范围
    int getFixedWidth();                                                            //返回固定的宽度
    int getFixedHeight();                                                           //返回固定的长度
    void setHeight(int height);

    void addText(const QString &text,double x_coord,double y_coord);                //给每一个导联添加名字
    QCustomPlot* getCustomPlot();                                                   //返回customPlot

    void plot(const vector<double> &xAxisData, const vector<double> &yAxisData);
    void addTimeText(const QString text);                                           //在左上角添加时间文本
    void setGrid();                                                                 //设置网格样式
    void clearAllGraph();                                                           //清除所有的图
    bool eventFilter(QObject *obj, QEvent *event);
signals:

public slots:
};

#endif // ECGGRAPH_H
