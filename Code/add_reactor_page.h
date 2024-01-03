#ifndef ADD_REACTOR_PAGE_H
#define ADD_REACTOR_PAGE_H

#include <QWidget>
#include "extend.h"
namespace Ui {
class Add_Reactor_page;
}

class Add_Reactor_page : public QWidget
{
    Q_OBJECT

public:
    explicit Add_Reactor_page(int createORchange = 0,QWidget *parent = nullptr);//0代表创建，1代表修改
    int createORchange;
    ~Add_Reactor_page();
    Reactor new_reactor();//增加的反应器

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();


private:
    Ui::Add_Reactor_page *ui;
};

#endif // ADD_REACTOR_PAGE_H
