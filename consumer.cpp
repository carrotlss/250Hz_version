#include "consumer.h"


void Consumer::run(){
    int files = 0;

    for(point = 0;point<effnum/3*times;point++)
    {
        Point p;
        int flag;

        MyQueue::getGlobalInstance().get(&p);
        if(point == (effnum/3*times-1))
        {
            flag = -1;
        }
        if(mode == 1)
        {
            int filestop = p.savedat((flag));
            if(filestop != files)
            {
                files++;
                if(filestop == files)
                {
                    emit savdatnum(filestop);
                }

            }
        }
        else if(mode == 2)
        {
            int filestop = p.savedat2((flag));
            if(filestop != files)
            {
                files++;
                if(filestop == files)
                {
                    emit savdatnum(filestop);
                }

            }
        }             
    }
//    if(res!=0){
//        qDebug()<<"消费者出错或者结束";
//        emit consumerstopflag();
//        break;
//    }

    emit consumerstopflag();
}
