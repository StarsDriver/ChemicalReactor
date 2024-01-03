#ifndef PRE_CHOOSE_H
#define PRE_CHOOSE_H

#include <QWidget>

namespace Ui {
class pre_choose;
}

class pre_choose : public QWidget
{
    Q_OBJECT

public:
    explicit pre_choose(QWidget *parent = nullptr);
    ~pre_choose();

public slots:   //需要声明为公共槽
    void chooseAreactor(int i);

private slots:
    void on_pushButton_clicked();

private:
    Ui::pre_choose *ui;
};

#endif // PRE_CHOOSE_H
