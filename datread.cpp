#include "datread.h"

Datread::Datread()
{

}

void Datread::run()
{
    qDebug()<<"readData线程开始";
    if(mode == 1)
    {
        byteread_pos(filepath, pos, len,*axisX,*axisCH);
    }
    else if(mode == 2)
    {
        byteread_pos2(filepath, pos, len,*axisX,*axisCH2);
    }

    return;
}

void Datread::byteread_pos(const QString &path,int pos,int len,vector<double> &axisX,vector<vector<double> > &axisCH)
{
    axisX.clear();
    for (size_t i =0;i<axisCH.size();++i)
    {
        axisCH[i].clear();
    }

    QString datpath = path;
    FILE *fp = nullptr;
    fp = fopen(datpath.toLocal8Bit().data(),"rb");    //fopen打开的是char，把Qstring转为char;toLocal8Bit支持中文
    if(fp == nullptr)
    {
        qDebug() << "fail to open the file!";
        return;
    }
//    BYTE* read_data_buff ;
    BYTE read_data_buff[len];
    BYTE* window_chenck_p;

    fseek(fp,0,SEEK_END);  //文件指针指向偏移位置
    int file_size = ftell(fp);  //获取文件首到当前位置的字节数
    fseek(fp,pos,SEEK_SET);  //文件指针指向偏移位置
//    read_data_buff = new BYTE[len];  //缓存区
    if(len > file_size - pos)
    {
        int len_part1 = file_size - pos;
        int len_part2 = len - len_part1;
        size_t res_read1= fread(read_data_buff,1,size_t(len_part1),fp);//fread的返回值含义为：读到的块数
        if(res_read1 != size_t(len_part1))
        {
            qDebug() << "读取文件失败";
//            delete read_data_buff;
            fclose(fp);
            return;
        }

        int cntpath = datpath.length();
//        int i = datpath.lastIndexOf("/");
//        QString str = datpath.right(cntpath-i-1);
        int j = datpath.lastIndexOf("_");
        int ser = datpath.right(cntpath-j-1).toInt();
        datpath = datpath.replace(cntpath-j-1,4,ser+1);
        FILE *fp = nullptr;
        fp = fopen(datpath.toLocal8Bit().data(),"rb");    //fopen打开的是char，把Qstring转为char;toLocal8Bit支持中文
        if(fp == nullptr)
        {
            return;
        }
        fseek(fp,0,SEEK_SET);  //文件指针指向偏移位置
        size_t res_read2= fread(read_data_buff+len_part1,1,len_part2,fp);//fread的返回值含义为：读到的块数
        if(res_read2 != size_t(len_part2))
        {
//            delete read_data_buff;
            fclose(fp);
            return;
        }
    }
    else
    {
        size_t res_read= fread(read_data_buff,1,len,fp);//fread的返回值含义为：读到的块数
        if(res_read == 0)
        {
//            delete read_data_buff;
            fclose(fp);
            return;
        }
    }
    fclose(fp);

    window_chenck_p = read_data_buff;
    double axis_time= 0.0;

    while((window_chenck_p - read_data_buff)!=len)  //数据读完
    {

        int32_t res_1 = ((int32_t)(((uint32_t)(*(window_chenck_p + 3)) << 16 | ((uint32_t)(*(window_chenck_p + 4))) << 8 | (*(window_chenck_p + 5))) << 8)) / 256;
        int32_t res_2 = ((int32_t)(((uint32_t)(*(window_chenck_p + 6)) << 16 | ((uint32_t)(*(window_chenck_p + 7))) << 8 | (*(window_chenck_p + 8))) << 8)) / 256;
        int32_t res_3 = ((int32_t)(((uint32_t)(*(window_chenck_p + 9)) << 16 | ((uint32_t)(*(window_chenck_p + 10))) << 8 | (*(window_chenck_p + 11))) << 8)) / 256;
        int32_t res_4 = ((int32_t)(((uint32_t)(*(window_chenck_p + 12)) << 16 | ((uint32_t)(*(window_chenck_p + 13))) << 8 | (*(window_chenck_p + 14))) << 8)) / 256;
        int32_t res_5 = ((int32_t)(((uint32_t)(*(window_chenck_p + 15)) << 16 | ((uint32_t)(*(window_chenck_p + 16))) << 8 | (*(window_chenck_p + 17))) << 8)) / 256;
        int32_t res_6 = ((int32_t)(((uint32_t)(*(window_chenck_p + 18)) << 16 | ((uint32_t)(*(window_chenck_p + 19))) << 8 | (*(window_chenck_p + 20))) << 8)) / 256;
        int32_t res_7 = ((int32_t)(((uint32_t)(*(window_chenck_p + 21)) << 16 | ((uint32_t)(*(window_chenck_p + 22))) << 8 | (*(window_chenck_p + 23))) << 8)) / 256;
//        int32_t res_8 = ((int32_t)(((uint32_t)(*(window_chenck_p + 24)) << 16 | ((uint32_t)(*(window_chenck_p + 25))) << 8 | (*(window_chenck_p + 26))) << 8)) / 256;

        window_chenck_p += 24; //指针便宜位置
        axisX.push_back(axis_time);
        axis_time+= 0.004;

        axisCH[0].push_back(double(res_1)/ 4194.3035);
        axisCH[1].push_back(double(res_2)/ 4194.3035);
        axisCH[2].push_back(double(res_3)/ 4194.3035);
        axisCH[3].push_back(double(res_4)/ 4194.3035);
        axisCH[4].push_back(double(res_5)/ 4194.3035);
        axisCH[5].push_back(double(res_6)/ 4194.3035);
        axisCH[6].push_back(double(res_7)/ 4194.3035);
//        axisCH[7].push_back(double(res_8)/ 4194.3035);
    }
//    delete read_data_buff;
    emit datready();
}

void Datread::byteread_pos2(const QString &path,int pos,int len,vector<double> &axisX,vector<double>  &axisCH2)
{
    axisX.clear();
    axisCH2.clear();

    QString datpath = path;
    FILE *fp = nullptr;
    fp = fopen(datpath.toLocal8Bit().data(),"rb");    //fopen打开的是char，把Qstring转为char;toLocal8Bit支持中文
    if(fp == nullptr)
    {
        qDebug() << "fail to open the file!";
        return;
    }
//    BYTE* read_data_buff ;
    BYTE read_data_buff[len];
    BYTE* window_chenck_p;

    fseek(fp,0,SEEK_END);  //文件指针指向偏移位置
    int file_size = ftell(fp);  //获取文件首到当前位置的字节数
    fseek(fp,pos,SEEK_SET);  //文件指针指向偏移位置
//    read_data_buff = new BYTE[len];  //缓存区
    if(len > file_size - pos)
    {
        int len_part1 = file_size - pos;
        int len_part2 = len - len_part1;
        size_t res_read1= fread(read_data_buff,1,size_t(len_part1),fp);//fread的返回值含义为：读到的块数
        if(res_read1 != size_t(len_part1))
        {
            qDebug() << "读取文件失败";
//            delete read_data_buff;
            fclose(fp);
            return;
        }

        int cntpath = datpath.length();
//        int i = datpath.lastIndexOf("/");
//        QString str = datpath.right(cntpath-i-1);
        int j = datpath.lastIndexOf("_");
        int ser = datpath.right(cntpath-j-1).toInt();
        datpath = datpath.replace(cntpath-j-1,4,ser+1);
        FILE *fp = nullptr;
        fp = fopen(datpath.toLocal8Bit().data(),"rb");    //fopen打开的是char，把Qstring转为char;toLocal8Bit支持中文
        if(fp == nullptr)
        {
            return;
        }
        fseek(fp,0,SEEK_SET);  //文件指针指向偏移位置
        size_t res_read2= fread(read_data_buff+len_part1,1,len_part2,fp);//fread的返回值含义为：读到的块数
        if(res_read2 != size_t(len_part2))
        {
//            delete read_data_buff;
            fclose(fp);
            return;
        }
    }
    else
    {
        size_t res_read= fread(read_data_buff,1,len,fp);//fread的返回值含义为：读到的块数
        if(res_read == 0)
        {
//            delete read_data_buff;
            fclose(fp);
            return;
        }
    }
    fclose(fp);

    window_chenck_p = read_data_buff;
    double axis_time= 0.0;

    while((window_chenck_p - read_data_buff)!=len)  //数据读完
    {

        int32_t res_1 = ((int32_t)(((uint32_t)(*(window_chenck_p + 3)) << 16 | ((uint32_t)(*(window_chenck_p + 4))) << 8 | (*(window_chenck_p + 5))) << 8)) / 256;
//            int32_t res_2 = ((int32_t)(((uint32_t)(*(window_chenck_p + 6)) << 16 | ((uint32_t)(*(window_chenck_p + 7))) << 8 | (*(window_chenck_p + 8))) << 8)) / 256;
//            int32_t res_3 = ((int32_t)(((uint32_t)(*(window_chenck_p + 9)) << 16 | ((uint32_t)(*(window_chenck_p + 10))) << 8 | (*(window_chenck_p + 11))) << 8)) / 256;
//            int32_t res_4 = ((int32_t)(((uint32_t)(*(window_chenck_p + 12)) << 16 | ((uint32_t)(*(window_chenck_p + 13))) << 8 | (*(window_chenck_p + 14))) << 8)) / 256;
//            int32_t res_5 = ((int32_t)(((uint32_t)(*(window_chenck_p + 15)) << 16 | ((uint32_t)(*(window_chenck_p + 16))) << 8 | (*(window_chenck_p + 17))) << 8)) / 256;
//            int32_t res_6 = ((int32_t)(((uint32_t)(*(window_chenck_p + 18)) << 16 | ((uint32_t)(*(window_chenck_p + 19))) << 8 | (*(window_chenck_p + 20))) << 8)) / 256;
//            int32_t res_7 = ((int32_t)(((uint32_t)(*(window_chenck_p + 21)) << 16 | ((uint32_t)(*(window_chenck_p + 22))) << 8 | (*(window_chenck_p + 23))) << 8)) / 256;
//        int32_t res_8 = ((int32_t)(((uint32_t)(*(window_chenck_p + 24)) << 16 | ((uint32_t)(*(window_chenck_p + 25))) << 8 | (*(window_chenck_p + 26))) << 8)) / 256;

        window_chenck_p += 3; //指针便宜位置
        axisX.push_back(axis_time);
        axis_time+= 0.000125;

        axisCH2.push_back(double(res_1)/ 4194.3035+60);
//            axisCH[1].push_back(double(res_2)/ 4194.3035);
//            axisCH[2].push_back(double(res_3)/ 4194.3035);
//            axisCH[3].push_back(double(res_4)/ 4194.3035);
//            axisCH[4].push_back(double(res_5)/ 4194.3035);
//            axisCH[5].push_back(double(res_6)/ 4194.3035);
//            axisCH[6].push_back(double(res_7)/ 4194.3035);
//        axisCH[7].push_back(double(res_8)/ 4194.3035);
    }
//    delete read_data_buff;
    emit datready();

}
