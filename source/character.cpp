#include "character.h"
#include<QPixmap>
#include<QPainter>


character::character()
{
    x=10;
    y=18;
    width=1;
    height=2;
    status=RUN;

    painter=new QPainter;

    pic_run=new QPixmap[5];
    pic_run[0].load(":/images/images/run1.png");
    pic_run[1].load(":/images/images/run2.png");
    pic_run[2].load(":/images/images/run3.png");
    pic_run[3].load(":/images/images/run4.png");
    pic_run[4].load(":/images/images/run5.png");


    pic_up =new QPixmap;
    pic_up->load(":/images/images/jump1.png");
    pic_down=new QPixmap;
    pic_down->load(":/images/images/jump2.png");

    present_status=pic_run;
};
character::~character()
{}
void character::show(QPaintDevice* de)
{

    painter->begin(de);
    painter->drawPixmap(x*20,200+30*(y-height+1),*present_status);
    painter->end();
}
void character::run()
{
    present_status=pic_run;
    status=RUN;
}
void character::jump()
{
    status=UP;
    present_status=pic_up;
    power=6;
}
void character::up()
{
    switch(power--)
    {
    case 6:
    case 5:
    case 4:
{y-=2;break;}
    case 3:
    case 2:
    case 1:
        y--;
    }
}
void character::down()
{
    status=DOWN;
    present_status=pic_down;
    y++;
}
