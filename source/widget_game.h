#ifndef WIDGET_GAME_H
#define WIDGET_GAME_H

#include<QGraphicsView>
#include<QGraphicsScene>
#include<qpainter.h>
#include "character.h"
#include<QTimer>
#include <QWidget>
#include<QPushButton>
#include<QKeyEvent>
#include"widget_aftergame.h"
#include<QLabel>
struct point
{
    int x,y;
};

namespace Ui {
class widget_game;
}

class widget_game : public QWidget
{
    Q_OBJECT

public:
    explicit widget_game(QWidget *parent = nullptr);
    ~widget_game();
    void paintEvent(QPaintEvent *event);


    QFrame* frame;//游戏界面
    widget_aftergame* aftergame;//游戏结束后的界面

    QPushButton *btnStart;//开始按钮
    QTimer* timer1;//计时器
    QPainter *painter;
    QBrush *brush;

    /*场景中的元素*/
    character* Character;
    int ground[20][100];//用一个二维数组模拟游戏场景
    base *pb1=NULL,*pb2=NULL,*pb3=NULL,*pb4=NULL,*pb5=NULL;//五种障碍物的指针
    int score;//得分
    QPixmap* coin;
    point *getcoin[15];
    int speed;//刷新率
    QLabel* showscore;


    bool eventFilter(QObject *watched, QEvent *event);//重载事件过滤器，用于在frame界面上进行绘制
    void keyPressEvent(QKeyEvent * event);

    /*功能函数*/
    void show_scene();
    base* create();//随机创建障碍物
        int ran1();
        int ran2(int);
    bool blockrun();
    int oo,old;
    int speedlevel1();
    int speedlevel2();
    int speedlevel3();

private:
    Ui::widget_game *ui;

signals:
    void back();//向主菜单窗口发送信号，返回主界面
private slots:
    void start();//触发时游戏开始
    void gaming();//触发代表游戏继续进行
    void gameover();//触发后游戏结束
    void gotomain();//触发后返回主菜单

};
#endif // WIDGET_GAME_H
