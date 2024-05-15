#include "block.h"

void block2::note(int ground[20][100])
{
    for(int j=y;j>y-height;j--)
    {
        for(int i=x;i<x+width;i++)
        {
            if(i>=0&&j>=0&&i<100&&j<20)
            {
                if(j==y)ground[j][i]=1;
                if(j==y-height+1&&i>=x+14&&i<=x+17){ground[j][i]=2;}
            }
        }
    }
}
void block3::note(int ground[20][100])
{
    for(int j=y;j>y-height;j--)
    {
        for(int i=x;i<x+width;i++)
        {
           if(i>=0&&j>=0&&i<100&&j<20)
            {
                if(j==y-5&&i>x+17&&i<x+33){ground[j][i]=1;}
                if(j==y-4&&i>x+17&&i<x+33){ground[j][i]=1;}
                if(j==y-3&&i>x+17&&i<x+33){ground[j][i]=1;}
                if(j==y-2&&(i<x+15||i>x+35)){ground[j][i]=1;}
                if(j==y-1&&(i<x+15||i>x+35)){ground[j][i]=1;}
                if(j==y-1&&(i>x+22&&i<x+28)){ground[j][i]=3;}
                if(j==y){ground[j][i]=1;}
            }
        }
    }
}
void block4::note(int ground[20][100])
{
    for(int j=y;j>y-height;j--)
    {
        for(int i=x;i<x+width;i++)
        {
           if(i>=0&&j>=0&&i<100&&j<20)
            {
                if(j==y-5&&i>x+24&&i<x+28){ground[j][i]=3;qWarning("coincreat--------------------");}
                if(j==y-5&&i>x+18&&i<x+22){ground[j][i]=2;}
                if(j==y-4&&i>x+12&&i<x+34){ground[j][i]=1;}
                if(j==y-3&&i>x+12&&i<x+34){ground[j][i]=1;}
                if(j==y-2&&(i<x+9||i>x+37)){ground[j][i]=1;}
                if(j==y-1&&(i<x+9||i>x+37)){ground[j][i]=1;}
                if(j==y){ground[j][i]=1;}
            }
        }
    }
}
void block5::note(int ground[20][100])
{
    for(int j=y;j>y-height;j--)
    {
        for(int i=x;i<x+width;i++)
        {
           if(i>=0&&j>=0&&i<100&&j<20)
            {
                if(j==y-5&&i>=x+27&&i<=x+33)ground[j][i]=3;
                if(j==y-4&&i>=x+25&&i<=x+35)ground[j][i]=1;
                if(j==y-2&&(i<x+5||i>x+55))ground[j][i]=1;
                if(j==y-1&&(i<x+10||i>x+50))ground[j][i]=1;
                if(j==y-1&&i>=x+12&&i<=x+16)ground[j][i]=2;
                if(j==y-1&&i>=x+44&&i<=x+48)ground[j][i]=2;
                if(j==y)ground[j][i]=1;
            }
        }
    }
}

