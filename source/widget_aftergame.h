#ifndef WIDGET_AFTERGAME_H
#define WIDGET_AFTERGAME_H

#include <QWidget>
#include<QFrame>
#include<QPushButton>
#include<QLabel>
#include<QSpacerItem>
namespace Ui {
class widget_aftergame;
}

class widget_aftergame : public QWidget
{
    Q_OBJECT

public:
    explicit widget_aftergame(int score,QWidget *parent = nullptr);
    ~widget_aftergame();

    int score;
    QLabel guide;
    QSpacerItem *item1,*item2;


    void stay(std::string &name,std::string &score);


signals:
    void btnclicked();
private slots:
    void on_btnAccept_clicked();
    void on_btnNegative_clicked();

private:
    Ui::widget_aftergame *ui;
};

#endif // WIDGET_AFTERGAME_H
