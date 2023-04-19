#include "ecggraph.h"

ECGGraph::ECGGraph(QCustomPlot *customPlot) : customGraphPlot(customPlot)
{
    customGraphPlot->setInteractions( QCP::iRangeZoom | QCP::iSelectPlottables);
//    customGraphPlot->setInteractions(QCP::iRangeDrag | QCP::iSelectPlottables);
//    height=customGraphPlot->height();
//    width=customGraphPlot->width();
    customGraphPlot->installEventFilter(this);
}

ECGGraph::~ECGGraph()
{

}
//设置为固定的大小
void ECGGraph::setFixedSize(int width, int height)
{
    this->width = width;
    this->height = height;
    customGraphPlot->setFixedSize(width,height);
    customGraphPlot->replot();
}
//
void ECGGraph::setHeight(int height)
{
    this->height = height;
    customGraphPlot->setFixedHeight(height);
    customGraphPlot->replot();
}
//设置画笔的颜色
void ECGGraph::setPen(QPen pen)
{
    this->pen = pen;
}

void ECGGraph::setxAxisRange(double start, double end)
{
    customGraphPlot->xAxis->setRange(start,end);

}
//设置Y轴的范围
void ECGGraph::setyAxisRange(double start, double end)
{
    customGraphPlot->yAxis->setRange(start,end);
}
void ECGGraph::plot(const vector<double> &xAxisData, const vector<double> &yAxisData)
{
    if(xAxisData.size()==0 || yAxisData.size()==0 || xAxisData.size()!=yAxisData.size()) return;
    customGraphPlot->addGraph();    //添加一个曲线图
    int graphIndex = customGraphPlot->graphCount() - 1;     //因为要画12个,所有要这样写,当前的曲线图
    customGraphPlot->graph(graphIndex)->setPen(pen);
    QVector<double> axisX_temp= QVector<double>::fromStdVector(xAxisData);
    QVector<double> axisY_temp= QVector<double>::fromStdVector(yAxisData);
    customGraphPlot->graph(graphIndex)->addData(axisX_temp, axisY_temp);
    customGraphPlot->replot();
}

//给每一个导联添加名字
void ECGGraph::addText(const QString &text, double x_coord, double y_coord)
{
    QCPItemText *textLabel = new QCPItemText(customGraphPlot);
    textLabel->setPen(QPen(Qt::NoPen));//无边框
    textLabel->setPadding(QMargins(8,2,2,2));//文字距离边框几个像素
    textLabel->setPositionAlignment(Qt::AlignVCenter|Qt::AlignLeft);//对齐
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);//对齐方式
    textLabel->position->setCoords(x_coord, y_coord);//坐标
    //字体和颜色
    textLabel->setFont(QFont("SimSun", 15));
    textLabel->setColor(Qt::black);
    textLabel->setText(text);
}
//在左上角添加时间文本
void ECGGraph::addTimeText(const QString text)
{
    QCPItemText *timeText = new QCPItemText(customGraphPlot);
    timeText->setPositionAlignment(Qt::AlignLeft);//文字布局：顶、左对齐
    timeText->setPadding(QMargins(10,2,2,2));//文字距离边框几个像素
    timeText->position->setType(QCPItemPosition::ptAxisRectRatio);//位置类型（当前轴范围的比例为单位/实际坐标为单位）
    timeText->position->setCoords(0, 0); //把文字框放在左上角
    timeText->setFont(QFont("SimSun", 10));
    timeText->setColor(Qt::black);
    timeText->setText(text);
}
//设置网格样式
void ECGGraph::setGrid()
{
    customGraphPlot->xAxis->setTicks(false);
//    customGraphPlot->yAxis->setTicks(false);
    //设置固定的刻度
//    customGraphPlot->xAxis->ticker()->setTickCount(26);//11个主刻度
//    customGraphPlot->yAxis->ticker()->setTickCount(26);//11个主刻度
    //以步长来画刻度
    QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
    customGraphPlot->xAxis->setTicker(fixedTicker);
    fixedTicker->setTickStep(0.2); // tick step shall be 1.0
    fixedTicker->setScaleStrategy(QCPAxisTickerFixed::ssNone);

    QSharedPointer<QCPAxisTickerFixed> fixedTicker2(new QCPAxisTickerFixed);
    customGraphPlot->yAxis->setTicker(fixedTicker2);
    fixedTicker2->setTickStep(0.2); // tick step shall be 1.0
    fixedTicker2->setScaleStrategy(QCPAxisTickerFixed::ssNone);

//    customGraphPlot->xAxis->grid()->setSubGridVisible(true);//显示x轴子网格线
    customGraphPlot->xAxis->grid()->setPen(QPen(Qt::red, 0.15));
    customGraphPlot->yAxis->grid()->setPen(QPen(Qt::red, 0.15));
}

QCustomPlot* ECGGraph::getCustomPlot()
{
    return customGraphPlot;
}
void ECGGraph::clearAllGraph()
{
//    customGraphPlot->clearPlottables();
    customGraphPlot->clearItems();
    customGraphPlot->clearGraphs();
}

bool ECGGraph::eventFilter(QObject *obj, QEvent *event)
{
//    static double count=0;
//    if(obj == static_cast<QObject *>(customGraphPlot))
//    {
//        if(event->type() == QEvent::Wheel)
//        {
//            auto e=dynamic_cast<QWheelEvent*>(event);
//            count+=e->delta();
//            qDebug()<<count;
//            if(count<-600 || count>800)
//            {
//                count = count>0?800:-600;
//                return true;
//            }
//        }
//    }
    return false;
}
