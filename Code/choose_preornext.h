#ifndef CHOOSE_PREORNEXT_H
#define CHOOSE_PREORNEXT_H

#include <QWidget>

namespace Ui {
class choose_preornext;
}

class choose_preornext : public QWidget
{
    Q_OBJECT

public:
    explicit choose_preornext(QWidget *parent = nullptr);
    ~choose_preornext();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::choose_preornext *ui;
};

#endif // CHOOSE_PREORNEXT_H
