#include "widget_main.h"
#include <QApplication>
#include<QSound>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    widget_main w;
    w.show();
    /*设置背景音乐*/
    QSound bgm(":/bgm/bgm/Adam Young - Southampton (online-audio-converter.com).wav");
    bgm.setLoops(-1);
    bgm.play();

    return a.exec();
}
