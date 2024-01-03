#ifndef CHOOSE_REACTOR_TOCHANGE_H
#define CHOOSE_REACTOR_TOCHANGE_H

#include <QWidget>

namespace Ui {
class choose_reactor_tochange;
}

class choose_reactor_tochange : public QWidget
{
    Q_OBJECT

public:
    explicit choose_reactor_tochange(QWidget *parent = nullptr);
    ~choose_reactor_tochange();
public slots:
    void chooseAreactor(int i);

private:
    Ui::choose_reactor_tochange *ui;
};

#endif // CHOOSE_REACTOR_TOCHANGE_H
