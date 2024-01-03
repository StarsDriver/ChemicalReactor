#ifndef NET_SHOW_H
#define NET_SHOW_H

#include <QWidget>
#include <vector>
#include <QLabel>
#include"GlobalManage.h"
using namespace std;
namespace Ui {
class net_show;
}

class net_show : public QWidget
{
    Q_OBJECT

public:
    explicit net_show(QWidget *parent = nullptr);
    ~net_show();
    bool is_pause;
    vector<QLabel*> all_labs;//记录所有展示反应器的标签,方便进行更新
    vector<Pos_recoder> POS;
    vector<QLabel*> all_oports_labs;//记录所有展示输出端口的标签，方便更新
    vector<QLabel*> all_iports_labs;//记录输入端口
private slots:
    void on_Add_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_Go_clicked();

    void on_Pause_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::net_show *ui;
};

#endif // NET_SHOW_H
