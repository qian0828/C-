#ifndef DLG_ADDUSER_H
#define DLG_ADDUSER_H

#include <QDialog>
#include"stusql.h"
namespace Ui {
class Dlg_AddUser;
}

class Dlg_AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_AddUser(QWidget *parent = nullptr);
    ~Dlg_AddUser();

    void setType2(bool isAdd, UserInfo info={});
private slots:

    void on_btn_save2_clicked();

    void on_btn_cancel2_clicked();

private:
    Ui::Dlg_AddUser *ui;
    bool m_isAdd2;
    UserInfo m_info2;
};

#endif // DLG_ADDUSER_H
