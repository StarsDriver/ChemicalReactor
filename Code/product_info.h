#ifndef PRODUCT_INFO_H
#define PRODUCT_INFO_H

#include <QWidget>

namespace Ui {
class Product_info;
}

class Product_info : public QWidget
{
    Q_OBJECT

public:
    explicit Product_info(QWidget *parent,int CreateOrChange =0);
    int CreateOrChange =0;
    ~Product_info();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Product_info *ui;
};

#endif // PRODUCT_INFO_H
