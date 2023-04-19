#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent),mainwindow(new MainWindow)
{
    savefilenum = 0;
    axisX=new vector<double>();
    axisCH=new vector<vector<double>>(7);//250Hz的7个采样通道
    connect(mainwindow,&MainWindow::readfromdisk,this,&Controller::startread);
    connect(mainwindow,SIGNAL(SliderValueChange(int)),this,SLOT(plotGraph_view(int)));//刷新图片
//    position = 0;

}

Controller::~Controller()
{
    delete mainwindow;
}

void Controller::startshow()
{
    mainwindow->show();
}

void Controller::startread()
{
    savefilenum = 0;
    producer = new Producer;
    consumer = new Consumer;

    producer -> address = mainwindow -> address;
    producer -> offset = mainwindow -> offset;
    producer -> times = mainwindow -> times;
    producer -> datanum = mainwindow -> datanum;
    producer -> headnum = mainwindow -> headnum;
    producer -> effnum = mainwindow -> effnum;
    idatlength = mainwindow -> idatlength;   

    connect(consumer,SIGNAL(savdatnum(int)),this,SLOT(plotshowinit(int)));

    connect(producer,&Producer::producerstopflag,this,[&](){
        producer->quit();
        producer->wait();
        delete producer;
        qDebug() << "生产者线程销毁";
    });
    connect(consumer,&Consumer::consumerstopflag,this,[&](){
        consumer->quit();
        consumer->wait();
        delete consumer;
        qDebug() << "消费者线程销毁";
    });

    producer -> start();
    consumer -> start();
}


//图片显示初始化,滑块更新
void Controller::plotshowinit(int inum)
{
//    qDebug() << "show";
    QString showpath = "D:\\lusisi\\qt_study\\2023.4.19\\storage\\savedata_0.dat";
    int showpos = 0;
//    int showlen = 1080000;//5s的长度
    int showlen = 30000;//5s的长度
    if(savefilenum != inum)
    {
        savefilenum++;
        if(savefilenum == inum )
        {
            if(savefilenum == 1)
            {
                if(idatlength<5)//每张图显示5s
                {
                    datread = new Datread;
                    datread->axisX=this->axisX;
                    datread->axisCH=this->axisCH;
                    datread->filepath = showpath;
                    datread->pos = showpos;
                    datread->len = 24*250*idatlength;//250Hz 7个通道
                    connect(datread,&Datread::datready,this,[&](){
                        datread->quit();
                        datread->wait();
                        delete datread;
                        qDebug() << "init read";
                        plotGraph_preview();
                    });
                    datread -> start();
                }
                else
                {
                    datread = new Datread;
                    datread->axisX=this->axisX;
                    datread->axisCH=this->axisCH;
                    datread->filepath = showpath;
                    datread->pos = showpos;
                    datread->len = showlen;
                    connect(datread,&Datread::datready,this,[&](){
                        datread->quit();
                        datread->wait();
                        delete datread;
                        qDebug() << "init read";
                        plotGraph_preview();
                    });
                    datread -> start();
                }

            }
            if(idatlength>5)//数据小于5s滑块无初始化
            {
                if(savefilenum<((idatlength-1)/lenfile+1))
                {
                    mainwindow ->initializ_Slider(savefilenum*lenfile);
                }
                else
                {
                    mainwindow ->initializ_Slider(idatlength);
                }
            }
            qDebug() << "slider refresh";

        }
        else
        {
            savefilenum--;
        }
    }
//    else
//    {
//        //重新读取5s数据
//        datread = new Datread;
//        datread->axisX=this->axisX;
//        datread->axisCH=this->axisCH;

//        QString aFileName = QString("D:\\lusisi\\qt_study\\2023.2.6\\storage\\savedata_%1.dat").arg(pos/lenfile);
//        qDebug() << aFileName;
//        datread->filepath = aFileName;
//        datread->pos = (pos%lenfile)*27*8000;
//        datread->len = 27*8000*5;
//        connect(datread,&Datread::datready,this,[&](){
//            datread->quit();
//            datread->wait();
//            delete datread;
//            plotGraph_preview();
//        });
//        datread -> start();

//    }

}

void Controller::plotGraph_preview()
{
    mainwindow->plotGraph_preview(*axisX,*axisCH);
}

void Controller::plotGraph_view(int pos)
{
    qDebug() << "plot refresh";
    //重新读取5s数据
    datread = new Datread;
    datread->axisX=this->axisX;
    datread->axisCH=this->axisCH;
    QString aFileName = QString("D:\\lusisi\\qt_study\\2023.4.19\\storage\\savedata_%1.dat").arg(pos/lenfile);
    qDebug() << aFileName;
    datread->filepath = aFileName;
    datread->pos = (pos%lenfile)*24*250;
    datread->len = 24*250*5;
    connect(datread,&Datread::datready,this,[&](){
        datread->quit();
        datread->wait();
        delete datread;
        qDebug() << "refresh plot";
        mainwindow->plotGraph_preview(*axisX,*axisCH);
    });
    datread -> start();
}
