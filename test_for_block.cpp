#include <iostream>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<ctime>
using namespace std;

int k[20][100]={0};//这就是整个场景，宽100高20
int power=0;
int score=0;
class base
{
public:
    int x,y,h,w;
    int speed;
    base(int a,int b,int c,int d,int s):x(a),y(b),h(c),w(d),speed(s){}
    virtual ~base(){}
    void jump();//角色跳跃函数
    void run(int a=1);//向左移动
    void up(int a=1);//向上移动
    void down(int a=1);//向下移动
    virtual void note();//在场景矩阵中标记自己的位置
};
class basefloor:public base
{
public:
    basefloor(int a=1,int b=16,int c=1,int d=95,int s=1):base(a,b,c,d,s){}
};
class block1:public base
{
public:
    block1(int a,int b,int c=1,int d=30,int s=1):base(a,b,c,d,s){}
};
class block2:public base
{
public:
    block2(int a,int b,int c=2,int d=30,int s=1):base(a,b,c,d,s){}
    void note();
};
class block3:public base
{
public:
    block3(int a,int b,int c=6,int d=40,int s=1):base(a,b,c,d,s){}
    void note();
};
class block4:public base
{
public:
    block4(int a,int b,int c=6,int d=40,int s=1):base(a,b,c,d,s){}
    void note();
};
base* pb1,*pb2,*pb3,*pb4,*pb5;
void scan();//接收键盘输入的空格
void print1();//打印一长条100格‘*’
void gotoxy(int x,int y);//用来清屏的函数，相比于system("cls")这个不会闪烁,要清屏时直接打gotoxy(0,0);
void HideCursor();//隐藏光标的函数
void show();//将场景打印出来
void control();//主控函数
bool blockrun();//障碍运行的程序
base* creat();//随机创建一个新的障碍

int main()
{
    pb1=NULL,pb2=NULL,pb3=NULL,pb4=NULL,pb5=NULL;
    pb1=new basefloor;
    pb1->note();
    control();
    return 0;
}

void show()//将场景打印出来
{
    gotoxy(0,0);
    HideCursor();
    for(int j=0;j<20;j++)//j控制打印y坐标
    {
        for(int i=0;i<100;i++)//i控制打印x坐标
        {
            switch (k[j][i])
            {
                case -2:cout<<'\b'<<"你";break;
                case -1:cout<<'\b'<<"人";break;
                case 0:cout<<" ";break;
                case 1:cout<<"▏";break;
                case 2:cout<<'\b'<<"▲";break;
            }//cout<<k[j][i];▲▍
        }
        cout<<endl;
    }
    print1();
}

void control()//主控函数——————————————————————————————————————————————————————————！！！
{
    base you(20,15,2,1,1);//玩家人物角色
    while(1)
    {
        gotoxy(0,0);
        HideCursor();
        if(blockrun())break;//障碍运行的程序
        if(k[you.y+1][you.x]!=0){power=0;}//一旦接触到地板立即重置跳跃能力
        if(kbhit())//若按了键则真，没按则假
        {
            string ss;
            ss=getch();
            if(ss==" ")
            {
                if(k[you.y+1][you.x]!=0){power=5;}
            }
        }
        you.jump();
        if(k[you.y+1][you.x]==0&&power<0)//若不踩在场景上，而且不在跳跃过程中，就下落
        {
            you.down(you.speed);
        }
        if(power==0){power--;}
        if(k[you.y][you.x]==0||k[you.y][you.x]==-1)k[you.y][you.x]=-1;
        else break;
    	if(k[you.y-you.h+1][you.x]==0||k[you.y-you.h+1][you.x]==-2)k[you.y-you.h+1][you.x]=-2;
    	else break;
        if(k[you.y+1][you.x]==2)break;
    	if(you.y>=19)break;
        show();//将场景打印出来
        cout<<"得分："<<score++;
    }
    cout<<"游戏结束，您的得分为："<<score<<endl;
}
bool blockrun()//障碍运行的程序
{
    int t=0;//临时变量判断是否
    for(int j=0;j<20;j++)
    {
        for(int i=95;i<100;i++)
        {
            if(k[j][i]!=0){t=1;}//最右边空出来5格位置了才能创建新的障碍
        }
    }
    if(!t){creat();}//—————————————————————————————————————————————————有问题，可能会出现两个间隔太远的情况
    if(pb1!=NULL)
    {
        if(pb1->x+pb1->w>0)
        {
            pb1->run(pb1->speed);
            pb1->note();
        }//没走到最左边，就继续运行；
        else
        {
            delete pb1;
            pb1=NULL;
        }//若到了最左边离开场景，则删除
    }
    if(pb2!=NULL)
    {
        if(pb2->x+pb2->w>0)
        {
            pb2->run(pb2->speed);
            pb2->note();
        }//没走到最左边，就继续运行；
        else{delete pb2;pb2=NULL;}//若到了最左边离开场景，则删除
    }
    if(pb3!=NULL)
    {
        if(pb3->x+pb3->w>0)
        {
            pb3->run(pb3->speed);pb3->note();
        }//没走到最左边，就继续运行；
        else{delete pb3;pb3=NULL;}//若到了最左边离开场景，则删除
    }
    if(pb4!=NULL)
    {
        if(pb4->x+pb4->w>0)
        {
            pb4->run(pb4->speed);pb4->note();
        }//没走到最左边，就继续运行；
        else{delete pb4;pb4=NULL;}//若到了最左边离开场景，则删除
    }
    if(pb5!=NULL)
    {
        if(pb5->x+pb5->w>0)
        {
            pb5->run(pb5->speed);pb5->note();
        }//没走到最左边，就继续运行；
        else{delete pb5;pb5=NULL;}//若到了最左边离开场景，则删除
    }
    return false;
}
base* creat()//随机创建一个新的障碍,返回指向新障碍的指针
{
    int t,tt;//临时变量储存随机值
    srand((unsigned)time(NULL));//根据时间取得随机数函数rand()的种子;
    t=rand()%4+1;//取得1~5之间的随机数
    tt=rand()%4+15;//取得15~19之间的随机数,作为障碍物的y坐标
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

    }
}
void print1()//打印一长条‘*’
{
    for(int i=0;i<100;i++)
    {
        cout<<'*';
    }
    cout<<endl;
}

void gotoxy(int x,int y)//用来清屏的函数，清屏时直接打gotoxy(0,0)，相比于system("cls")这个不会闪烁
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y =y;
	SetConsoleCursorPosition(handle,pos);
}
void HideCursor()//隐藏光标的函数
{
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}



//以下是成员函数
void base::note()//在场景矩阵中标记自己的位置
{
    for(int j=y;j>y-h;j--)
    {
        for(int i=x;i<x+w;i++)
        {
            if(i>=0&&j>=0&&i<100&&j<20)k[j][i]=1;
        }
    }
}
void base::jump()//角色跳跃函数
{
    if(power==5){this->up(3),power--;}
    else if(power<=4&&power>3){this->up(2),power--;}
    else if(power<=3&&power>2){this->up(1),power--;}
    else if(power<=2&&power>1){this->up(0),power--;}
    else if(power<=1&&power>0){this->up(0),power--;}
}
void base::run(int a)//向左移动
{
	for(int j=y;j>y-h;j--)//清除移动前的记录
	{
		for(int i=x;i<x+w;i++){if(i>=0&&j>=0&&i<100&&j<20)k[j][i]=0;}
	}
	x-=a;
}
void base::up(int a)//向上移动
{
	for(int j=y;j>y-h;j--)//清除移动前的记录
	{
		for(int i=x;i<x+w;i++){if(i>=0&&j>=0&&i<100&&j<20)k[j][i]=0;}
	}
	y-=a;
}
void base::down(int a)//向下移动
{
	for(int j=y;j>y-h;j--)//清除移动前的记录
	{
		for(int i=x;i<x+w;i++){if(i>=0&&j>=0&&i<100&&j<20)k[j][i]=0;}
	}
	y+=a;
}
void block2::note()
{
    for(int j=y;j>y-h;j--)
    {
        for(int i=x;i<x+w;i++)
        {
            if(i>=0&&j>=0&&i<100&&j<20)
            {
                if(j==y)k[j][i]=1;
                if(j==y-h+1&&i>=x+14&&i<=x+18){k[j][i]=2;}
            }
        }
    }
}
void block3::note()
{
    for(int j=y;j>y-h;j--)
    {
        for(int i=x;i<x+w;i++)
        {
           if(i>=0&&j>=0&&i<100&&j<20)
            {
                if(j==y-5&&i>x+12&&i<x+28){k[j][i]=1;}
                if(j==y-4&&i>x+12&&i<x+28){k[j][i]=1;}
                if(j==y-3&&i>x+12&&i<x+28){k[j][i]=1;}
                if(j==y-2&&(i<x+10||i>x+30)){k[j][i]=1;}
                if(j==y-1&&(i<x+10||i>x+30)){k[j][i]=1;}
                if(j==y){k[j][i]=1;}
            }
        }
    }
}
void block4::note()
{
    for(int j=y;j>y-h;j--)
    {
        for(int i=x;i<x+w;i++)
        {
           if(i>=0&&j>=0&&i<100&&j<20)
            {
                if(j==y-5&&i>x+12&&i<x+28){k[j][i]=2;}
                if(j==y-4&&i>x+12&&i<x+28){k[j][i]=1;}
                if(j==y-3&&i>x+12&&i<x+28){k[j][i]=1;}
                if(j==y-2&&i<x+9||i>x+31){k[j][i]=1;}
                if(j==y-1&&i<x+9||i>x+31){k[j][i]=1;}
                if(j==y){k[j][i]=1;}
            }
        }
    }
}
