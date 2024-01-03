#ifndef ADD_IPORT_PRO_H
#define ADD_IPORT_PRO_H

#include <QWidget>

namespace Ui {
class add_iport_pro;
}

class add_iport_pro : public QWidget
{
    Q_OBJECT

public:
    explicit add_iport_pro(QWidget *parent = nullptr);
    ~add_iport_pro();

private slots:
    void on_pushButton_clicked();

private:
    Ui::add_iport_pro *ui;
};

#endif // ADD_IPORT_PRO_H
