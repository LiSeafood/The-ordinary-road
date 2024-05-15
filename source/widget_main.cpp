#include "widget_main.h"
#include "ui_widget_main.h"
#include"widget_game.h"

widget_main::widget_main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_main)
{

    ui->setupUi(this);

}

widget_main::~widget_main()
{
    delete ui;
}

void widget_main::on_btnNew_clicked()
{
    Widget=new widget_game;
    connect(Widget,SIGNAL(back()),this,SLOT(reshow()));
    Widget->show();
    this->hide();
}

void widget_main::reshow()
{
    qWarning("roger");
    this->show();

}

void widget_main::on_btnRank_clicked()
{
    Widget=new widget_rank;
    Widget->show();
}


void widget_main::on_btnHelp_clicked()
{

    Widget=new widget_help;
    Widget->show();
}

