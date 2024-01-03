#ifndef CHOOSE_OPORT_PRE_H
#define CHOOSE_OPORT_PRE_H

#include <QWidget>

namespace Ui {
class choose_oport_pre;
}

class choose_oport_pre : public QWidget
{
    Q_OBJECT

public:
    explicit choose_oport_pre(QWidget *parent = nullptr);
    ~choose_oport_pre();
public slots:
    void chooseAreactor(int i);

private:
    Ui::choose_oport_pre *ui;
};

#endif // CHOOSE_OPORT_PRE_H
