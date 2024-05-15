#ifndef WIDGET_HELP_H
#define WIDGET_HELP_H

#include <QWidget>

namespace Ui {
class widget_help;
}

class widget_help : public QWidget
{
    Q_OBJECT

public:
    explicit widget_help(QWidget *parent = nullptr);
    ~widget_help();

private:
    Ui::widget_help *ui;
};

#endif // WIDGET_HELP_H
