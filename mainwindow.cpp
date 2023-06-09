#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialize_Plot();
    sliderflag = 0;
    //当滑块松开时发送信号
    connect(ui->horizontalSlider,&QSlider::sliderReleased,this,[&](){
    position =int(ui->horizontalSlider->value());
//        if(length_copy < 5) return;//读取数据小于5s
    if(sliderflag)
    {
        if(position>(isliderlen - 5))//
        {
            position = isliderlen - 5;
        }
        qDebug() << "emit the signal";
        emit SliderValueChange(position);
    }


        });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_read_clicked()
{

    ui->read->setEnabled(false);
    if(ui->address->text().trimmed()==""||ui->offset->text().trimmed()==""||ui->times->text().trimmed()==""||ui->datanum->text().trimmed()==""||ui->headnum->text().trimmed()==""||ui->effnum->text().trimmed()=="")
    {
      QMessageBox::warning(this,"警告","输入参数不能为空！");
      ui->read->setEnabled(true);
    }
    else
    {
        address = ui->address->text();
        offset = ui->offset->text().toUInt();
        times = ui->times->text().toInt();
        datanum = ui->datanum->text().toInt();
        headnum = ui->headnum->text().toInt();
        effnum = ui->effnum->text().toInt();
//        idatlength = (times*effnum-1)/216000+1;//216000为8000Hz一秒的数据量
        idatlength = (times*effnum-1)/6000+1;


        emit readfromdisk();//发送读取信号
    }

}

//显示5s,若数据不足5s则显示5s内的数据
void MainWindow::plotGraph_preview(const vector<double> &axisX, const vector<vector<double>> &axisCH)
{
    ecgGraph_preview->clearAllGraph();
    ecgGraph_preview->setHeight(int(ui->scrollAreaWidgetContents->height()));

//    QString timeText = DateTime.addSecs(int(position/8000)).toString("yyyy-MM-dd hh:mm:ss");
//    ecgGraph_preview->addTimeText(timeText);
    int initlen;
    if(idatlength<5)
    {
        initlen = idatlength;
    }
    else
    {
        initlen = 5;
    }
    vector<double> X(axisX.begin(),axisX.begin()+(initlen*250));
    ecgGraph_preview->setxAxisRange(X.at(0),X.at(X.size()-1));
    qDebug() << "横轴尺寸" << X.size();
    ecgGraph_preview->setyAxisRange(-6,12);
//    ecgGraph_preview->setGrid();
//    QStringList list = {"1","2","3","4","5","6","7","8"};
    for(size_t i=0;i<axisCH.size();++i)
    {
        vector<double> Y(axisCH.at(i).begin(),axisCH.at(i).begin()+(initlen*250));
        for_each(Y.begin(), Y.end(), [=](double &a){a = a*0.12 + (6-i)*1.2;});
//        ecgGraph_preview->addText(list[int(i)],0,0.08*i+0.05);
        ecgGraph_preview->plot(X,Y);
    }
    //ecgGraph_preview->getCustomPlot()->replot();
}

void MainWindow::initialize_Plot()
{
    ecgGraph_preview = new ECGGraph(ui->customplot_preview);
}

//初始化滑块
void MainWindow::initializ_Slider(int length)
{
    isliderlen = length;
    ui->horizontalSlider->initialization = true;
    ui->horizontalSlider->initialize_slider(isliderlen);
    sliderflag = 1;
//    //当滑块松开时发送信号
//    connect(ui->horizontalSlider,&QSlider::sliderReleased,this,[&](){
//    position =int(ui->horizontalSlider->value());
////        if(length_copy < 5) return;//读取数据小于5s
//    if(position>(isliderlen - 5))//
//    {
//        position = isliderlen - 5;
//    }
//    qDebug() << "emit the signal";
//    emit SliderValueChange(position);

//    });



}

//void MainWindow::plotGraph_view(const vector<double> &axisX, const vector<vector<double>> &axisCH)
//{
//    ecgGraph_preview->clearAllGraph();
//    ecgGraph_preview->setHeight(int(ui->scrollAreaWidgetContents->height()));
//    vector<double> X(axisX.begin(),axisX.begin()+5*8000);//5s的显示
//    ecgGraph_preview->setxAxisRange(X.at(0),X.at(X.size()-1));
//    ecgGraph_preview->setyAxisRange(-1,10);

//    for(size_t i=0;i<axisCH.size();++i)
//    {
//        vector<double> Y(axisCH.at(i).begin(),axisCH.at(i).begin()+5*8000);
//        for_each(Y.begin(), Y.end(), [=](double &a){a = a*0.15 + (7-i)*1.2;});
//        ecgGraph_preview->plot(X,Y);
//    }

//}
