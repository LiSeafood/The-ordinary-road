#ifndef WIDGET_MAIN_H
#define WIDGET_MAIN_H

#include <QWidget>
#include"widget_game.h"
#include"widget_rank.h"
#include"widget_help.h"
#include<QSound>
namespace Ui {
class widget_main;
}

class widget_main : public QWidget
{
    Q_OBJECT

public:
    explicit widget_main(QWidget *parent = nullptr);
    ~widget_main();
    QWidget* Widget;

private slots:
    void on_btnNew_clicked();
    void reshow();
    void on_btnRank_clicked();
    void on_btnHelp_clicked();

private:
    Ui::widget_main *ui;
};

#endif // WIDGET_MAIN_H
