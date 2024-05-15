#ifndef BASE_H
#define BASE_H

#include<QPainter>
#include<QWidget>
class base
{
public:
    int x,y,height,width;//物体左下角的坐标，高度和宽度
    virtual void run();//人和建筑物的运动方式不同
    base(int x,int y,int height,int width);
    base();
    ~base();

    virtual void show(QPaintDevice*);
    virtual void note(int ground[20][100]);
};

#endif // BASE_H
