#include "widget_game.h"
#include "ui_widget_game.h"
#include<string.h>
#include<ctime>
#include<QColorDialog>
#include"frame.h"
#include"block.h"

#include"widget_aftergame.h"
#include<thread>
widget_game::widget_game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_game)
{
    ui->setupUi(this);
            /*初始化游戏界面，贴上游戏背景*/
            frame=new QFrame(this);
            frame->setObjectName(QString::fromUtf8("frame"));
            frame->setGeometry(QRect(0, 0, 2000, 1000));
            frame->setStyleSheet(QString::fromUtf8("#frame{background-image: url(:/images/gamebg1);}"));
            frame->setFrameShape(QFrame::StyledPanel);
            frame->setFrameShadow(QFrame::Raised);
            frame->installEventFilter(this);

            btnStart=new QPushButton(frame);
            btnStart->resize(167,89);
            btnStart->move(900,450);
            btnStart->setStyleSheet("QPushButton{border-image:url(:/images/images/startbutton.png)}");
            connect(btnStart,SIGNAL(clicked()),this,SLOT(start()));//连接按钮的信号槽

            coin=new QPixmap(":/images/images/coin.png");
            for(int i=0;i<15;i++)getcoin[i]=NULL;
            painter=new QPainter;
            brush=new QBrush;
            brush->setColor(Qt::yellow);
            brush->setStyle(Qt::SolidPattern);
            painter->setBrush(*brush);



    /*显示得分*/
    showscore=new QLabel;
    showscore->setParent(frame);
    showscore->setGeometry(240,900,200,50);

    showscore->setFont(QFont("\344\273\277\345\256\213",30));

    /*创立一个角色*/
    Character=new character;
    memset(ground,0,sizeof ground);//将场景数组初始化为0
    score=0;

    /*设定初始速度为0.1秒移动一次*/
    speed=100;

    /*设定开始高度*/
    old=0;

}

widget_game::~widget_game()
{
    delete ui;
}
int widget_game::speedlevel1()
{speed=75;timer1->setInterval(75);return 0;}
int widget_game::speedlevel2()
{speed=60;timer1->setInterval(60);return 0;}
int widget_game::speedlevel3()
{speed=50;timer1->setInterval(50);return 0;}

void widget_game::paintEvent(QPaintEvent *event){}//重载绘制事件，但由于无法直接在子控件frame上绘制，所以需要重载事件过滤器
void widget_game::show_scene()
{
    QPolygon triangle;
    painter->begin(frame);
    painter->setBrush(*brush);
    int i,j;
    for(i=0;i<20;i++)
        for(j=0;j<100;j++)
        {
            if(ground[i][j]==1)
            {
                painter->fillRect(20*j,200+30*i,20,30,Qt::white);
            }
            else if(ground[i][j]==2)
            {
                triangle.setPoints(3,20*j,230+30*i,20*j+10,200+30*i,20*j+20,230+30*i);
                painter->drawConvexPolygon(triangle);
            }
            else if(ground[i][j]==3)
            {
                painter->drawPixmap(20*j,200+30*i,20,30,*coin);
            }
        }
    painter->end();
}

bool widget_game::eventFilter(QObject *watched,QEvent *event)//重载事件过滤器，在子控件frame上绘制
{
    if(watched==frame&&event->type()==QEvent::Paint)//如果子控件为frame且事件为paint，则在frame上进行绘制
    {
        Character->show(frame);//绘制角色
        show_scene();//绘制场景
        return true;
    }
    else
        return QWidget::eventFilter(watched,event);//否则交给基类的事件过滤器处理
}
//槽函数
void widget_game::start()//游戏开始
{
    Character->run();//人物开始跑动
    this->btnStart->close();
    this->setFocus();//将widget设置为焦点，使其能够接受键盘事件
    pb1=new block1(0,19,95,1);//建立初始地面

    /*设置每0.1秒对场景进行刷新*/
    timer1=new QTimer;
    timer1->start(speed);
    connect(timer1,SIGNAL(timeout()),this,SLOT(gaming()));
}
void widget_game::gaming()//游戏进行
{
    blockrun();

    /*检测角色周围是否有致命物体*/
    if(ground[Character->y-1][Character->x+1]==1
    ||ground[Character->y-1][Character->x+1]==2
    ||ground[Character->y][Character->x+1]==1//身前有障碍物
    ||ground[Character->y][Character->x+1]==2//身前有刺
    ||(Character->y)>18//脚下是底边界
    ||ground[Character->y+1][Character->x]==2)//脚下是刺
    {
        qWarning("gameover");
        gameover();//游戏结束
        return;
    }

    /*检测主角是否拾取到金币*/
    if(ground[Character->y][Character->x]==3)//如果撞到金币
    {
        ground[Character->y][Character->x]=0;
        int i;
        for(i=0;i<15&&getcoin[i]!=NULL;i++);//找到一个空闲指针
        getcoin[i]=new point;
        getcoin[i]->x=Character->x;
        getcoin[i]->y=Character->y;//标记该点
        score+=10;qWarning("getcoin");
    }
    if(ground[Character->y-1][Character->x]==3)
    {
        ground[Character->y-1][Character->x]=0;
        int i;
        for(i=0;i<15&&getcoin[i]!=NULL;i++);//找到一个空闲指针
        getcoin[i]=new point;
        getcoin[i]->x=Character->x;
        getcoin[i]->y=Character->y-1;//标记该点
        score+=10;qWarning("getcoin");
    }
    /*将已经被拾起的金币抹去,
    更新已经标记的金币状态*/
    for(int i=0;i<15;i++)
    {
        if(getcoin[i]==NULL)continue;//跳过空指针
        else
        {
            ground[getcoin[i]->y][getcoin[i]->x]=0;
            getcoin[i]->x--;
            if(getcoin[i]->x<0)
            {
                delete(getcoin[i]);
                getcoin[i]=NULL;
            }
        }
    }

    /*检验角色状态是否需要更换*/
    if(Character->status==RUN)
    {
        Character->present_status++;
        if(Character->present_status>Character->pic_run+4)
            Character->present_status=Character->pic_run;
        if(Character->y<19&&ground[Character->y+1][Character->x]==0)
            Character->down();
    }
    else if(Character->status==UP)
    {
        Character->up();
        if(Character->power==0)//当power值降为0时，判断其脚下是否接触地面
            if(ground[Character->y+1][Character->x]==1)
                Character->run();
            else
                Character->down();
    }
    else if(Character->status==DOWN)
    {
        Character->y++;
        if(Character->y>=19||ground[Character->y+1][Character->x]==1)//如果接触到地面（或接触到底边界）
        {
            Character->run();//状态切换为跑步
        }
    }
    /*重置角色的跳跃能力*/
    if(Character->status==RUN&&ground[Character->y+1][Character->x]==1)
        {Character->bjump=true;}
    else Character->bjump=false;

    update();//更新界面，触发paintevent
    score++;//增加分数
    showscore->setText(QString::number(score));
    if(score>800)static int temp3=speedlevel3();
    else if(score>600)static int temp2=speedlevel2();
    else if(score>400)static int temp1=speedlevel1();//利用静态变量的特点保证速度只会改变一次
}
void widget_game::gameover()//游戏结束
{
    timer1->stop();
    aftergame=new widget_aftergame(score);
    aftergame->show();
    connect(aftergame,SIGNAL(btnclicked()),this,SLOT(gotomain()));//连接信号槽，当点击按钮时结束窗口，返回到主菜单
}
void widget_game::gotomain()//返回主菜单
{
    qWarning("close");
    /**/
    this->aftergame->close();
    delete(this->aftergame);
    /**/
    this->close();

    emit back();

    delete(this);
}
void widget_game::keyPressEvent(QKeyEvent *event)//读取键盘事件，按空格时跳跃
{
    if(event->key()==Qt::Key_Space&&Character->bjump)//当按下空格并且满足跳跃条件时
    {
        Character->jump();
    }
    /*
    else if(event->key()==Qt::Key_Escape)
    {
        pause();
    }*/
}

bool widget_game::blockrun()//障碍运行的程序
{
    bool flag=true;//临时变量判断是否
    for(int j=0;j<20;j++)
    {
        for(int i=95;i<100;i++)
        {
            if(ground[j][i]!=0){flag=false;}//最右边空出来5格位置了才能创建新的障碍
        }
    }
    memset(ground,0,sizeof ground);
    if(flag){create();}//—————————————————————————————————————————————————有问题，可能会出现两个间隔太远的情况
    if(pb1!=NULL)
    {
        if(pb1->x+pb1->width>0)
        {
            pb1->run();
            pb1->note(ground);

        }//没走到最左边，就继续运行；
        else
        {
            delete pb1;
            pb1=NULL;
        }//若到了最左边离开场景，则删除
    }
    if(pb2!=NULL)
    {
        if(pb2->x+pb2->width>0)
        {
            pb2->run();
            pb2->note(ground);
        }//没走到最左边，就继续运行；
        else{delete pb2;pb2=NULL;}//若到了最左边离开场景，则删除
    }
    if(pb3!=NULL)
    {
        if(pb3->x+pb3->width>0)
        {
            pb3->run();pb3->note(ground);
        }//没走到最左边，就继续运行；
        else{delete pb3;pb3=NULL;}//若到了最左边离开场景，则删除
    }
    if(pb4!=NULL)
    {
        if(pb4->x+pb4->width>0)
        {
            pb4->run();pb4->note(ground);
        }//没走到最左边，就继续运行；
        else{delete pb4;pb4=NULL;}//若到了最左边离开场景，则删除
    }
    if(pb5!=NULL)
    {
        if(pb5->x+pb5->width>0)
        {
            pb5->run();pb5->note(ground);
        }//没走到最左边，就继续运行；
        else{delete pb5;pb5=NULL;}//若到了最左边离开场景，则删除
    }
    return false;
}
base* widget_game::create()
{
    int t,tt;//临时变量储存随机值
    t=ran1();//随机数函数用来选择生成哪个障碍，不能连续生成，除了1、2
    tt=ran2(t);//随机生成障碍物高度，并且距离上一次不能太高导致跳不上去
    switch (t)//随机创建一个新的障碍
    {
    case 1:
        {
            if(pb1==NULL){pb1=new block1(100,tt);return pb1;}
            else if(pb2==NULL){pb2=new block1(100,tt);return pb2;}
            else if(pb3==NULL){pb3=new block1(100,tt);return pb3;}
            else if(pb4==NULL){pb4=new block1(100,tt);return pb4;}
            else if(pb5==NULL){pb5=new block1(100,tt);return pb5;}
            break;
        }
    case 2:
        {
            if(pb1==NULL){pb1=new block2(100,tt);return pb1;}
            else if(pb2==NULL){pb2=new block2(100,tt);return pb2;}
            else if(pb3==NULL){pb3=new block2(100,tt);return pb3;}
            else if(pb4==NULL){pb4=new block2(100,tt);return pb4;}
            else if(pb5==NULL){pb5=new block2(100,tt);return pb5;}
            break;
        }
    case 3:
        {
            if(pb1==NULL){pb1=new block3(100,tt);return pb1;}
            else if(pb2==NULL){pb2=new block3(100,tt);return pb2;}
            else if(pb3==NULL){pb3=new block3(100,tt);return pb3;}
            else if(pb4==NULL){pb4=new block3(100,tt);return pb4;}
            else if(pb5==NULL){pb5=new block3(100,tt);return pb5;}
            break;
        }
    case 4:
        {
            if(pb1==NULL){pb1=new block4(100,tt);return pb1;}
            else if(pb2==NULL){pb2=new block4(100,tt);return pb2;}
            else if(pb3==NULL){pb3=new block4(100,tt);return pb3;}
            else if(pb4==NULL){pb4=new block4(100,tt);return pb4;}
            else if(pb5==NULL){pb5=new block4(100,tt);return pb5;}
            break;
        }
    case 5:
        {
            if(pb1==NULL){pb1=new block5(100,tt);return pb1;}
            else if(pb2==NULL){pb2=new block5(100,tt);return pb2;}
            else if(pb3==NULL){pb3=new block5(100,tt);return pb3;}
            else if(pb4==NULL){pb4=new block5(100,tt);return pb4;}
            else if(pb5==NULL){pb5=new block5(100,tt);return pb5;}
            break;
        }
    }
}
int widget_game::ran1()//随机数函数用来选择生成哪个障碍，不能连续生成，除了1、2
{
    int t;
    static int old;//用于记录上一次生成的是哪个障碍
    srand((unsigned)time(NULL));//根据时间取得随机数函数rand()的种子;
    if(score<200)
    {
        t=rand()%2+1;
    }
    else if(score<400)
    {
        t=rand()%3+1;
        while(t==old&&old>2)
        {
            t=rand()%3+1;

        }
    }
    else if(score<600)
    {
        t=rand()%4+1;
        while(t==old&&old>2)
        {
            t=rand()%4+1;
        }
    }
    else if(score<800)
    {
        t=rand()%5+1;
        while(t==old&&old>2)
        {
            t=rand()%5+1;
        }
    }
    else if(score>=800)//——————————————————————————完全放开限制
    {
        t=rand()%5+1;
        while(t==old&&old>2)
        {
            t=rand()%5+1;
        }
    }
    old=t;
    return t;
}
int widget_game::ran2(int a=1)//随机生成障碍物高度，并且距离上一次不能太高导致跳不上去
{
    int tt;
    old=0;
    srand((unsigned)time(NULL));//根据时间取得随机数函数rand()的种子;
    if(old==0)tt=rand()%4+15;//初始高度控制在15~19之间
    else if(oo==5)
    {
        tt=rand()%6+old-3;
    }
    else if(oo==3||oo==4)
    {
        tt=rand()%6+old-4;
    }
    else if(oo==1||oo==2)
    {
        tt=rand()%6+old-2;
    }
    while(tt<10||tt>19)
    {
        if(oo==3||oo==4||oo==5)
        {
            tt=rand()%6+old-2;
        }
        else if(oo==1||oo==2)
        {
            tt=rand()%6+old-2;
        }
    }
    old=tt;
    oo=a;
    return tt;
}
