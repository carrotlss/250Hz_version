#include "slider.h"

Slider::Slider(QWidget *parent) : QSlider(parent)
{
    displayCurrentTime = new QLabel(this);
    this->setTracking(true);

}

Slider::~Slider()
{
    delete displayCurrentTime;
}
void Slider::initialize_slider(int length)
{    
    this->setMaximum(length);
    this->setMinimum(0);
//    this->setPageStep(1);
}

void Slider::mousePressEvent(QMouseEvent *event)//鼠标按下
{
//    if(!initialization ) return;
//    int currentX = event->pos().x();
//    double per = currentX *1.0 /this->width();
//    int value = int(per*(this->maximum() - this->minimum()) + this->minimum());
//    this->setValue(value);
    QSlider::mousePressEvent(event);
}
void Slider::mouseMoveEvent(QMouseEvent *event)//鼠标移动
{
//    if(!initialization ) return;
//    //获取当前点击位置
//    int currentX = event->pos().x();
//    //获取当前点击的位置占整个Slider的百分比
//    double per = currentX *1.0 /this->width();
//    //利用算得的百分比得到具体数字
//    int value = int(per*(this->maximum() - this->minimum()) + this->minimum());
//    //设定滑动条位置
//    this->setValue(value);
    //滑动条移动事件等事件也用到了mousePressEvent,加这句话是为了不对其产生影响，是的Slider能正常相应其他鼠标事件
    QSlider::mousePressEvent(event);
}

void Slider::mouseReleaseEvent(QMouseEvent *event)//鼠标松开
{
    if(!initialization) return;
    //获取当前点击位置
    int currentX = event->pos().x();
    //获取当前点击的位置占整个Slider的百分比
    double per = currentX *1.0 /this->width();
    //利用算得的百分比得到具体数字
    int value = int(per*(this->maximum() - this->minimum()) + this->minimum());
    //设定滑动条位置
    this->setValue(value);
    //滑动条移动事件等事件也用到了mousePressEvent,加这句话是为了不对其产生影响，是的Slider能正常相应其他鼠标事件
    QSlider::mouseReleaseEvent(event);
}
