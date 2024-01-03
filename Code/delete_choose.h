#ifndef DELETE_CHOOSE_H
#define DELETE_CHOOSE_H

#include <QWidget>

namespace Ui {
class delete_choose;
}

class delete_choose : public QWidget
{
    Q_OBJECT

public:
    explicit delete_choose(QWidget *parent = nullptr);
    ~delete_choose();
public slots:
    void chooseAreactor(int i);

private:
    Ui::delete_choose *ui;
};

#endif // DELETE_CHOOSE_H
