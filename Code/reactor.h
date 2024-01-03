#ifndef REACTOR_H
#define REACTOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Reactor; }
QT_END_NAMESPACE

class Reactor : public QMainWindow
{
    Q_OBJECT

public:
    Reactor(QWidget *parent = nullptr);
    ~Reactor();

private:
    Ui::Reactor *ui;
};
#endif // REACTOR_H
