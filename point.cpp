#include "point.h"
#include "QDebug"
#include <QDataStream>
#include "stdio.h"
#include"stdlib.h"


int Point::writenum = 0;
int Point::timenum = 0;
int Point::filenum = 0;
BYTE Point::onewrite[ONEWRITE_SIZE];

Point::Point(){
    m_data[PACKAGE_SIZE]=0x00;
    cur=0;
}
void Point::push(const BYTE &b){
    if(cur<PACKAGE_SIZE){
        m_data[cur++]=b;
    }
}
int Point::decode(){
    int res=((int)(((unsigned)(*(m_data + 0)) << 16 | ((unsigned)(*(m_data + 1))) << 8 |
                                            (*(m_data + 2))) << 8)) / 256;
    // 文件位置
    QFile file("D:\\lusisi\\qt_study\\2023.2.6\\test.txt");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        // 文件流
        QTextStream stream(&file);
        // 输入内容
        stream << res << endl;
    }
    else
    {
        qDebug()<<file.errorString();
    }

    file.close();

    return res;
}


int Point::savedat(int res){

    //    FILE *file = fopen("D:/lusisi/qt_study/savedata_0.dat","wb");
        QString aFileName = QString("D:\\lusisi\\qt_study\\2023.4.19\\storage\\savedata_%1.dat").arg(filenum);
    //    file = fopen(aFileName.toLocal8Bit().data(),"w+");


    if(res!=0)
    {
        if(writenum == 0)
        {
//            if(timenum%80 == 0)//如果是8000采样，判断是否整秒数
//            {
//                filenum++;
//                timenum = 0;
////                qDebug() << filenum;
//                return filenum;
//            }
//            else
//            {
//                for(int i=0;i<ONEWRITE_SIZE;++i){
//                    onewrite[i] = 0;
//                }
//                for(int i =0; i<80-(timenum%80); i++)
//                {
//                    FILE *file = fopen(aFileName.toStdString().c_str(),"ab");
//                    if(!file)
//                    {
//                        qDebug() << "fail to open the file";
//                        return 0;
//                    }
//                    fseek(file,(timenum+i)*ONEWRITE_SIZE,SEEK_SET);
//                    size_t re_read = fwrite(onewrite,1,ONEWRITE_SIZE,file);
//                    if(re_read == 0)
//                    {
//                        qDebug() << "未写入成功";
//        //                delete read_data_buff_stop;
//                        fclose(file);
//                        return 0;
//                    }

//                    fclose(file);

//                }
//                filenum++;
//                timenum = 0;
//    //            qDebug() << filenum;
//                return filenum;
//            }
            filenum++;
            timenum = 0;
//                qDebug() << filenum;
            return filenum;
        }
        else
        {

            FILE *file = fopen(aFileName.toStdString().c_str(),"ab");
            if(!file)
            {
                qDebug() << "fail to open the file";
                return 0;
            }
            for(int i=writenum;i<ONEWRITE_SIZE;++i){
                onewrite[i] = 0;
            }

            fseek(file,timenum*ONEWRITE_SIZE,SEEK_SET);
//            BYTE* read_data_buff_stop = onewrite;
//            read_data_buff_stop = new BYTE[writenum];  //缓存区
            size_t re_read = fwrite(onewrite,1,ONEWRITE_SIZE,file);
            if(re_read == 0)
            {
                qDebug() << "未写入成功";
//                delete read_data_buff_stop;
                fclose(file);
                return 0;
            }
            else
            {
//                delete read_data_buff_stop;
                fclose(file);
            }
//            if((timenum/80) < 79)
//            {
//                for(int i=0;i<ONEWRITE_SIZE;++i){
//                    onewrite[i] = 0;
//                }
//                for(int i =1; i<80-(timenum%80); i++)
//                {
//                    FILE *file = fopen(aFileName.toStdString().c_str(),"ab");
//                    if(!file)
//                    {
//                        qDebug() << "fail to open the file";
//                        return 0;
//                    }
//                    fseek(file,(timenum+i)*ONEWRITE_SIZE,SEEK_SET);
//                    size_t re_read = fwrite(onewrite,1,ONEWRITE_SIZE,file);
//                    if(re_read == 0)
//                    {
//                        qDebug() << "未写入成功";
//        //                delete read_data_buff_stop;
//                        fclose(file);
//                        return 0;
//                    }

//                    fclose(file);

//                }

//            }
            filenum++;
            writenum = 0;
            timenum = 0;
            return filenum;

        }
    }

    for(int i=0;i<PACKAGE_SIZE;++i){
        onewrite[writenum+i] = m_data[i];
    }
    writenum += 3;

    if(writenum == ONEWRITE_SIZE)
    {
        FILE *file = fopen(aFileName.toStdString().c_str(),"ab");
        if(!file)
        {
            qDebug() << "fail to open the file";
            return 0;
        }
        fseek(file,timenum*ONEWRITE_SIZE,SEEK_SET);
        writenum = 0;
//        BYTE* read_data_buff = onewrite;
//        read_data_buff = new BYTE[ONEWRITE_SIZE];  //缓存区
        size_t re_read = fwrite(onewrite,1,ONEWRITE_SIZE,file);
        if(re_read == 0)
        {
//            delete read_data_buff;
            fclose(file);
            return 0;
        }
//        delete read_data_buff;
        fclose(file);
//        qDebug() << "已读入一次数据";
        timenum++;
    }
    if(timenum>=WRITIMES)
    {
        filenum += 1;
        writenum = 0;
        timenum = 0;

    }
    return filenum;
}
