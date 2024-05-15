#include "widget_aftergame.h"
#include "ui_widget_aftergame.h"
#include <iostream>
#include <fstream>
#include "scorelist.h"
#include "time.h"

using std::string,std::ifstream,std::ios,std::ofstream,std::endl;



widget_aftergame::widget_aftergame(int score,QWidget *parent) :
    QWidget(parent),score(score),
    ui(new Ui::widget_aftergame)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags() );//设置无窗口框
    setAttribute(Qt::WA_TranslucentBackground);//设置背景透明

    item1=new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    item2=new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    ui->horizontalLayout_4->addItem(item1);
    ui->horizontalLayout_4->addWidget(&guide);
    ui->horizontalLayout_4->addItem(item2);//设置窗口布局，让label居中显示

    guide.setText(QString("游戏结束，您的分数为%1\n想要在排行榜中留下你的大名吗？").arg(score));
    guide.setFont(QFont("\344\273\277\345\256\213",20));//设置为仿宋字体，字号为20
    QPalette a;
    a.setColor(QPalette::WindowText,Qt::white);//字体颜色设置为白色
    guide.setPalette(a);
}

widget_aftergame::~widget_aftergame()
{
    delete ui;
}


void widget_aftergame::on_btnAccept_clicked()
{
    QString name;
    name=ui->inputLine->text();

    std::string std_name=name.toStdString();//将qstring转化为std::string

    std::string std_score=std::to_string(score);
    /*记录下来*/
    stay(std_name,std_score);
    emit btnclicked();
}
void widget_aftergame::on_btnNegative_clicked()
{
    emit btnclicked();
}


void widget_aftergame::stay(std::string &name,std::string &score)//将分数存储进排行榜
{
    {
        scorelist sl;
        string tn;
        sl.name=name;
        sl.scores=score;//分数化为字符串
        time_t now_time=time(NULL);//获取系统时间
        tm*  t_tm = localtime(&now_time);//获取本地时间
        sl.time=asctime(t_tm);
        sl.n="1";//排名默认为1，在排序的函数中会重新安排排名

        ofstream f1;
        f1.open("sss.txt",ios::app);
        if (!f1.is_open())
        {
            qWarning("打开文件失败");
        }
        f1<<sl.n<<endl;
        f1<<sl.name<<endl;
        f1<<sl.scores<<endl;
        f1<<sl.time<<endl;
        f1.close();
    }
}
