#ifndef FRAME_H
#define FRAME_H

#include<QFrame>
#include<QKeyEvent>
class myframe:public QFrame
{
public:
    myframe(QWidget *parent):QFrame(parent){};
    //void keyPressEvent(QKeyEvent *event);
};

#endif // FRAME_H
