#ifndef WIDGET_RANK_H
#define WIDGET_RANK_H

#include <QWidget>
#include"scorelist.h"
namespace Ui {
class widget_rank;
}

class widget_rank : public QWidget
{
    Q_OBJECT

public:
    explicit widget_rank(QWidget *parent = nullptr);
    ~widget_rank();

    int length();
    void showfile();
    void sortfile();

private:
    Ui::widget_rank *ui;
};

#endif // WIDGET_RANK_H
