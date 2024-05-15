#ifndef CHARACTER_H
#define CHARACTER_H

#include"base.h"
#include<QPixmap>

enum Status
{
    RUN,UP,DOWN
};

class character:public base
{
public:
    character();
    ~character();
    Status status;//枚举值表示角色当前状态
    bool bjump;//代表角色能否跳跃
    QPainter *painter;

    void show(QPaintDevice*);
    QPixmap *pic_run;//跑动的图片
    QPixmap *pic_up;//跳跃上升
    QPixmap *pic_down;//下降

    QPixmap *present_status;//当前播放的图片




    void run();
    void jump();
    int power;//power变量表示主角的跳跃状态，大于0时代表主角正在跳跃上升
    void up();//角色在power值大于0时上升
    void down();//在power值等于0且脚下没有接触地面时下降



};

#endif // CHARACTER_H
