#ifndef CHOOSE_IPORT_NEXT_H
#define CHOOSE_IPORT_NEXT_H

#include <QWidget>

namespace Ui {
class choose_iport_next;
}

class choose_iport_next : public QWidget
{
    Q_OBJECT

public:
    explicit choose_iport_next(QWidget *parent = nullptr);
    ~choose_iport_next();
public slots:
    void chooseAreactor(int i);
private:
    Ui::choose_iport_next *ui;
};

#endif // CHOOSE_IPORT_NEXT_H
