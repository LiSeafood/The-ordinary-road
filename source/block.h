#ifndef BLOCK_H
#define BLOCK_H

#include"base.h"
#include<QPainter>
class block1:public base
{
public:
    block1(int a,int b,int c=30,int d=1):base(a,b,c,d){}
};
class block2:public base
{
public:
    block2(int a,int b,int c=30,int d=2):base(a,b,c,d){}
    void note(int ground[20][100]);
};
class block3:public base
{
public:
    block3(int a,int b,int c=50,int d=6):base(a,b,c,d){}
    void note(int ground[20][100]);
};
class block4:public base
{
public:
    block4(int a,int b,int c=46,int d=6):base(a,b,c,d){}
    void note(int ground[20][100]);
};
class block5:public base
{
public:
    block5(int a,int b,int c=60,int d=6):base(a,b,c,d){}
    void note(int ground[20][100]);
};





#endif // BLOCK_H
