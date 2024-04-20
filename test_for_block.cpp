#include <iostream>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<ctime>
using namespace std;

int k[20][100]={0};//�����������������100��20
int power=0;
int score=0;
class base
{
public:
    int x,y,h,w;
    int speed;
    base(int a,int b,int c,int d,int s):x(a),y(b),h(c),w(d),speed(s){}
    virtual ~base(){}
    void jump();//��ɫ��Ծ����
    void run(int a=1);//�����ƶ�
    void up(int a=1);//�����ƶ�
    void down(int a=1);//�����ƶ�
    virtual void note();//�ڳ��������б���Լ���λ��
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
void scan();//���ռ�������Ŀո�
void print1();//��ӡһ����100��*��
void gotoxy(int x,int y);//���������ĺ����������system("cls")���������˸,Ҫ����ʱֱ�Ӵ�gotoxy(0,0);
void HideCursor();//���ع��ĺ���
void show();//��������ӡ����
void control();//���غ���
bool blockrun();//�ϰ����еĳ���
base* creat();//�������һ���µ��ϰ�

int main()
{
    pb1=NULL,pb2=NULL,pb3=NULL,pb4=NULL,pb5=NULL;
    pb1=new basefloor;
    pb1->note();
    control();
    return 0;
}

void show()//��������ӡ����
{
    gotoxy(0,0);
    HideCursor();
    for(int j=0;j<20;j++)//j���ƴ�ӡy����
    {
        for(int i=0;i<100;i++)//i���ƴ�ӡx����
        {
            switch (k[j][i])
            {
                case -2:cout<<'\b'<<"��";break;
                case -1:cout<<'\b'<<"��";break;
                case 0:cout<<" ";break;
                case 1:cout<<"��";break;
                case 2:cout<<'\b'<<"��";break;
            }//cout<<k[j][i];����
        }
        cout<<endl;
    }
    print1();
}

void control()//���غ�����������������������������������������������������������������������������������������������������������������������������
{
    base you(20,15,2,1,1);//��������ɫ
    while(1)
    {
        gotoxy(0,0);
        HideCursor();
        if(blockrun())break;//�ϰ����еĳ���
        if(k[you.y+1][you.x]!=0){power=0;}//һ���Ӵ����ذ�����������Ծ����
        if(kbhit())//�����˼����棬û�����
        {
            string ss;
            ss=getch();
            if(ss==" ")
            {
                if(k[you.y+1][you.x]!=0){power=5;}
            }
        }
        you.jump();
        if(k[you.y+1][you.x]==0&&power<0)//�������ڳ����ϣ����Ҳ�����Ծ�����У�������
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
        show();//��������ӡ����
        cout<<"�÷֣�"<<score++;
    }
    cout<<"��Ϸ���������ĵ÷�Ϊ��"<<score<<endl;
}
bool blockrun()//�ϰ����еĳ���
{
    int t=0;//��ʱ�����ж��Ƿ�
    for(int j=0;j<20;j++)
    {
        for(int i=95;i<100;i++)
        {
            if(k[j][i]!=0){t=1;}//���ұ߿ճ���5��λ���˲��ܴ����µ��ϰ�
        }
    }
    if(!t){creat();}//�������������������������������������������������������������������������������������������������������⣬���ܻ�����������̫Զ�����
    if(pb1!=NULL)
    {
        if(pb1->x+pb1->w>0)
        {
            pb1->run(pb1->speed);
            pb1->note();
        }//û�ߵ�����ߣ��ͼ������У�
        else
        {
            delete pb1;
            pb1=NULL;
        }//������������뿪��������ɾ��
    }
    if(pb2!=NULL)
    {
        if(pb2->x+pb2->w>0)
        {
            pb2->run(pb2->speed);
            pb2->note();
        }//û�ߵ�����ߣ��ͼ������У�
        else{delete pb2;pb2=NULL;}//������������뿪��������ɾ��
    }
    if(pb3!=NULL)
    {
        if(pb3->x+pb3->w>0)
        {
            pb3->run(pb3->speed);pb3->note();
        }//û�ߵ�����ߣ��ͼ������У�
        else{delete pb3;pb3=NULL;}//������������뿪��������ɾ��
    }
    if(pb4!=NULL)
    {
        if(pb4->x+pb4->w>0)
        {
            pb4->run(pb4->speed);pb4->note();
        }//û�ߵ�����ߣ��ͼ������У�
        else{delete pb4;pb4=NULL;}//������������뿪��������ɾ��
    }
    if(pb5!=NULL)
    {
        if(pb5->x+pb5->w>0)
        {
            pb5->run(pb5->speed);pb5->note();
        }//û�ߵ�����ߣ��ͼ������У�
        else{delete pb5;pb5=NULL;}//������������뿪��������ɾ��
    }
    return false;
}
base* creat()//�������һ���µ��ϰ�,����ָ�����ϰ���ָ��
{
    int t,tt;//��ʱ�����������ֵ
    srand((unsigned)time(NULL));//����ʱ��ȡ�����������rand()������;
    t=rand()%4+1;//ȡ��1~5֮��������
    tt=rand()%4+15;//ȡ��15~19֮��������,��Ϊ�ϰ����y����
    switch (t)//�������һ���µ��ϰ�
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
void print1()//��ӡһ������*��
{
    for(int i=0;i<100;i++)
    {
        cout<<'*';
    }
    cout<<endl;
}

void gotoxy(int x,int y)//���������ĺ���������ʱֱ�Ӵ�gotoxy(0,0)�������system("cls")���������˸
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y =y;
	SetConsoleCursorPosition(handle,pos);
}
void HideCursor()//���ع��ĺ���
{
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}



//�����ǳ�Ա����
void base::note()//�ڳ��������б���Լ���λ��
{
    for(int j=y;j>y-h;j--)
    {
        for(int i=x;i<x+w;i++)
        {
            if(i>=0&&j>=0&&i<100&&j<20)k[j][i]=1;
        }
    }
}
void base::jump()//��ɫ��Ծ����
{
    if(power==5){this->up(3),power--;}
    else if(power<=4&&power>3){this->up(2),power--;}
    else if(power<=3&&power>2){this->up(1),power--;}
    else if(power<=2&&power>1){this->up(0),power--;}
    else if(power<=1&&power>0){this->up(0),power--;}
}
void base::run(int a)//�����ƶ�
{
	for(int j=y;j>y-h;j--)//����ƶ�ǰ�ļ�¼
	{
		for(int i=x;i<x+w;i++){if(i>=0&&j>=0&&i<100&&j<20)k[j][i]=0;}
	}
	x-=a;
}
void base::up(int a)//�����ƶ�
{
	for(int j=y;j>y-h;j--)//����ƶ�ǰ�ļ�¼
	{
		for(int i=x;i<x+w;i++){if(i>=0&&j>=0&&i<100&&j<20)k[j][i]=0;}
	}
	y-=a;
}
void base::down(int a)//�����ƶ�
{
	for(int j=y;j>y-h;j--)//����ƶ�ǰ�ļ�¼
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
