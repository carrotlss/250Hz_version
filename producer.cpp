#include "producer.h"
#include <windows.h>
#include <stdio.h>
#include <QDebug>
#include "definition.h"


wchar_t *QString2Wchar(QString buf)
{
    return (wchar_t*)reinterpret_cast<const wchar_t *>(buf.utf16());
}

void Producer::run(){
    int cnt = 0;
    int sum = 0;
    int num = 0;
    BYTE buff[512*3];//读取缓存区

    DWORD bytesRead;


    QString adr = QString("\\\\.\\%1:").arg(address);
    qDebug() << adr;
    wchar_t *wcadr;
    wcadr = QString2Wchar(adr);

    HANDLE device = CreateFile(wcadr,    // Drive to open
                            GENERIC_READ,           // Access mode
                            FILE_SHARE_READ|FILE_SHARE_WRITE,        // Share Mode
                            NULL,                   // Security Descriptor
                            OPEN_EXISTING,          // How to create
                            0,                      // File attributes
                            NULL);                  // Handle to template
    if(device == INVALID_HANDLE_VALUE)
    {
        printf("CreateFile: %u\n", GetLastError());
        exit(0);
    }


    while (1) {
        //生产数据
        Point p;

        if(sum == 0)
        {
            //E00000 14680064
            SetFilePointer (device, offset+num*datanum+cnt*512*3, NULL, FILE_BEGIN) ;
            if (!ReadFile(device, buff, 512*3, &bytesRead, NULL))
            {
                qDebug()<<"The file handle is not open";
            }
            else
            {
//                qDebug()<<"Success!\n";
                //qDebug()<<"read byte length:"<<bytesRead;
        //        for(auto item:sector){
        //            qDebug()<<item;

             }
            if(cnt == 0)
            {
                sum = headnum;
            }
        }

        for(int i=0;i<PACKAGE_SIZE;++i){
            BYTE data=buff[sum++];
//            qDebug()<<data;
            p.push(data);
        }

        int res=MyQueue::getGlobalInstance().put(p);
        if(res!=0) {
            qDebug()<<"生产者出错或者结束";
            emit producerstopflag();

            break;
        }

        if(sum == 512*3)
        {
            cnt++;
            sum = 0;
        }

//        if(cnt == 10)
//        {
//            if(sum == ((datanum/512)%3)*512+effnum+headnum-datanum)
//            {
//                qDebug() << sum;
//                sum = 0;
//                cnt = 0;
//                num++;
//            }
//        }

        if(datanum/512/3 == 0)
        {
            if(cnt == datanum/512/3-1)
            {
                if(sum == effnum+headnum-datanum)
                {
                    sum = 0;
                    cnt = 0;
                    num++;
                }
            }
        }
        else
        {
            if(cnt == datanum/512/3)
            {
                if(sum == ((datanum/512)%3)*512+effnum+headnum-datanum)
                {
                    sum = 0;
                    cnt = 0;
                    num++;
                }
            }
        }


        //在生产完毕后终止线程 4098
        if(num >= times){
            qDebug()<<"数据戳数目为"<<num;
            MyQueue::getGlobalInstance().stop();
        }
    }
}

//void Producer::getaddress(QString str)
//{
//    address = str;
//    qDebug() << address;
//}

//void Producer::getoffset(uint uioffset)
//{
//    offset = uioffset;
//    qDebug() << offset;

//}

//void Producer::gettimes(int itimes)
//{
//    times = itimes;
//    qDebug() << times;

//}

//void Producer::getdatnum(int idatnum)
//{
//    datanum = idatnum;
//    qDebug() << datanum;

//}

//void Producer::getheadnum(int iheadnum)
//{
//    headnum = iheadnum;
//    qDebug() << headnum;
//}

//void Producer::geteffnum(int ieffnum)
//{
//    effnum = ieffnum;
//    qDebug() << effnum;

//}
