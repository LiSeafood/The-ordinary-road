#include "base.h"

base::base(int x, int y, int width, int height):x(x),y(y),height(height),width(width)
{
}
base::base()
{

}
base::~base()
{
}
void base::show(QPaintDevice *de)
{}
void base::run()
{
    x--;
}
void base::note(int ground[20][100])
{
    for(int j=y;j>y-height;j--)
    {
        for(int i=x;i<x+width;i++)
        {
            if(i>=0&&j>=0&&i<100&&j<20)ground[j][i]=1;
        }
    }
}
