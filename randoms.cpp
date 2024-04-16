#include <iostream>
#include "windows.h"
#include <ctime>
using namespace std;

int score=850;

int ran1()//随机数函数用来选择生成哪个障碍，不能连续生成，除了1、2
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
int ran2(int a=1)//随机生成障碍物高度，并且距离上一次不能太高导致跳不上去
{
    int tt;
    static int old=0;
    static int oo;
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
int main()
{

    int t,tt;
    for(int i=1;i<=20;i++)
    {
        t=ran1();
        tt=ran2(t);
        cout<<t<<" "<<tt<<endl;
        Sleep(500);
    }
    return 0;
}
