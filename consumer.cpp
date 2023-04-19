#include "consumer.h"


void Consumer::run(){

    while (1) {
        Point p;

        int res=MyQueue::getGlobalInstance().get(&p);
        int filestop = p.savedat((res));

        if(filestop)
        {
            emit savdatnum(filestop);
        }

        if(res!=0){
            qDebug()<<"消费者出错或者结束";
            emit consumerstopflag();
            break;
        }       


//        int data=p.decode();
//        qDebug()<<"解码得到数据："<<data;

    }
}
