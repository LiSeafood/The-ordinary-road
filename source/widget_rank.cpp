#include "widget_rank.h"
#include "ui_widget_rank.h"
#include<iostream>
#include<fstream>
#include"scorelist.h"
using std::string,std::ifstream,std::ios,std::ofstream,std::endl;
widget_rank::widget_rank(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_rank)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | windowFlags() );//设置无窗口框
    setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
    ui->listWidget->setFrameShape(QListWidget::NoFrame);//去掉窗口边框线
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//去掉界面的滚动条

    sortfile();
    showfile();//加载出排行榜

}

widget_rank::~widget_rank()
{
    delete ui;
}

int widget_rank::length()
{
    ifstream f2;
    string c;
    int i;
    f2.open("sss.txt",ios::in);
    for(i=0;i<100;i++)
    {
        getline(f2,c);
        if(c=="")break;//获取文件的行数
    }
    return (i+1)/4;
}

void widget_rank::showfile()//从文件中取得排行榜并打印出来
{
    scorelist s;
    ifstream f2;
    f2.open("sss.txt",ios::in);
    int n=length();
    QListWidgetItem* data[n];
    for(int i=0;i<n;i++)
    {
        getline(f2,s.n);
        if(s.n=="")break;
        getline(f2,s.name);
        getline(f2,s.scores);
        getline(f2,s.time);
        data[i]=new QListWidgetItem(QString(" No.%1攻略者：%2得分：%3%4").arg
        (QString::fromStdString(s.n),-5).arg
        (QString::fromStdString(s.name),-13).arg
        (QString::fromStdString(s.scores),-12).arg
        (QString::fromStdString(s.time),10)
        );//利用arg进行格式化输出，把各项数据转化为一条QString加入到listwiget中
        data[i]->setSizeHint(QSize(650,80));//调整大小
        data[i]->setFont(QFont("\344\273\277\345\256\213",11));
        ui->listWidget->addItem(data[i]);
    }

    f2.close();
}
void widget_rank::sortfile()//将文件中的排行榜进行排序
{

    ifstream f2;
    string c;
    int i,j,k;
    f2.open("sss.txt",ios::in);
    if (!f2.is_open())
    {
      qWarning("failed");return;
    }
    int n=length();
    scorelist s[n];
    int num[n];
    for(i=0;i<n;i++)
    {
        getline(f2,s[i].n);
        getline(f2,s[i].name);
        getline(f2,s[i].scores);
        num[i] = atoi(s[i].scores.c_str());
        getline(f2,s[i].time);
    }
    for(i=0;i<n-1;i++)//选择排序法
    {
        k=i;
        for(j=i+1;j<n;j++)
        {
            if(num[j]>num[k])
            {
                k=j;
            }
        }
        c=s[k].scores;
        s[k].scores=s[i].scores;
        s[i].scores=c;
        c=s[k].name;
        s[k].name=s[i].name;
        s[i].name=c;
        c=s[k].time;
        s[k].time=s[i].time;
        s[i].time=c;
    }
    f2.close();
    ofstream f1;//还要将排序后的数组输入到文件里去
    f1.open("sss.txt",ios::out);
    for(i=0;i<n;i++)
    {
        s[i].n=(i+1)+'0';
        f1<<s[i].n<<endl;
        f1<<s[i].name<<endl;
        f1<<s[i].scores<<endl;
        f1<<s[i].time<<endl;
    }
    f1.close();
}

