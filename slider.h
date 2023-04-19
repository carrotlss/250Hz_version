#ifndef SLIDER_H
#define SLIDER_H

// @brief 滑块的控件
// @birth created by BIGBAO on 20220208,15:20

#include <QObject>
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QDateTime>
#include <QDebug>
#include <QMouseEvent>

class Slider : public QSlider
{
    Q_OBJECT
public:
    explicit Slider(QWidget *parent = nullptr);
    ~Slider();
    bool initialization = true;
    void initialize_slider(int length);//初始化,滑块有多少个间隔
signals:
    void ValueChanged();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    QLabel *displayCurrentTime;
    QDateTime starttime;

public slots:
};

#endif // SLIDER_H
