#include "widget_help.h"
#include "ui_widget_help.h"

widget_help::widget_help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_help)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | windowFlags() );//设置无窗口框
    setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
    ui->label->adjustSize();
}

widget_help::~widget_help()
{
    delete ui;
}
