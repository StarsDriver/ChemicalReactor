#ifndef ADD_IPORT_H
#define ADD_IPORT_H

#include <QWidget>

namespace Ui {
class add_iport;
}

class add_iport : public QWidget
{
    Q_OBJECT

public:
    explicit add_iport(QWidget *parent = nullptr);
    ~add_iport();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::add_iport *ui;
};

#endif // ADD_IPORT_H
