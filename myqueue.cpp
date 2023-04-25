#include "myqueue.h"

MyQueue&  MyQueue::getGlobalInstance(){
    static MyQueue m_instance;
    return m_instance;
}
void MyQueue::stop(){
    mtx.lock();
    stopped=true;
    mtx.unlock();

}
int MyQueue::put(const Point &p){
    mtx.lock();
    if(stopped){
        mtx.unlock();
        return -1;
    }
    while(m_data.size()==BUFFER_SIZE){
        //等待消费者取出数据
        bufferNotFull.wait(&mtx);
    }
    m_data.push_back(p);

//    qDebug()<<m_data.size();
//    qDebug()<<"生产者放入数据";
    bufferNotEmpty.wakeAll();
    mtx.unlock();
    return 0;
}
int MyQueue::get(Point *p){
    mtx.lock();
    if(stopped||p==nullptr){

        if(m_data.size()==0)
        {
            mtx.unlock();
            return -1;
        }

    }
    while(m_data.size()==0){
        //等待生产者放入数据
        bufferNotEmpty.wait(&mtx);
    }

    auto tmp=m_data.front();
    m_data.pop_front();
    *p=tmp;
    bufferNotFull.wakeAll();
//    qDebug()<<"消费者取出数据";
    mtx.unlock();
    return 0;
}
