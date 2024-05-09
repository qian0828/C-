#include "dlg_adduser.h"
#include "ui_dlg_adduser.h"

#include <QMessageBox>

Dlg_AddUser::Dlg_AddUser(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dlg_AddUser)
{
    ui->setupUi(this);
}

void Dlg_AddUser::setType2(bool isAdd, UserInfo info)
{
    m_isAdd2 = isAdd;
    m_info2 = info;
    ui->le_password->setText(info.password);
    ui->le_auth->setText(info.auth);
}

Dlg_AddUser::~Dlg_AddUser()
{
    delete ui;
}

void Dlg_AddUser::on_btn_save2_clicked()
{
    QMessageBox::information(nullptr,"信息","存储成功");
    this->hide();
}


void Dlg_AddUser::on_btn_cancel2_clicked()
{
    this->hide();
}

