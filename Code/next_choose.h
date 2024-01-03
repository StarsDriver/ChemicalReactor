#ifndef NEXT_CHOOSE_H
#define NEXT_CHOOSE_H

#include <QWidget>

namespace Ui {
class next_choose;
}

class next_choose : public QWidget
{
    Q_OBJECT

public:
    explicit next_choose(QWidget *parent = nullptr);
    ~next_choose();
public slots:
    void chooseAreactor(int i);
private slots:
    void on_pushButton_clicked();
    
private:
    Ui::next_choose *ui;
};

#endif // NEXT_CHOOSE_H
