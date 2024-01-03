#ifndef ADD_IPORTOROPORT_H
#define ADD_IPORTOROPORT_H

#include <QWidget>

namespace Ui {
class add_iportoroport;
}

class add_iportoroport : public QWidget
{
    Q_OBJECT

public:
    explicit add_iportoroport(QWidget *parent = nullptr);
    ~add_iportoroport();

private:
    Ui::add_iportoroport *ui;
};

#endif // ADD_IPORTOROPORT_H
