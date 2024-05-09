#include "dlg_adduser.h"
#include "ui_dlg_adduser.h"
#include"stusql.h"
#include"QMessageBox"
Dlg_AddUser::Dlg_AddUser(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dlg_AddUser)
{
    ui->setupUi(this);
}

Dlg_AddUser::~Dlg_AddUser()
{
    delete ui;
}

void Dlg_AddUser::setType2(bool isAdd, UserInfo info)
{
    m_isAdd2 = isAdd;
    m_info2 = info;
    ui->le_username->setText(info.username);
    ui->le_password->setText(info.password);
    ui->le_auth->setText(info.auth);
}



void Dlg_AddUser::on_btn_save2_clicked()
{
    UserInfo info;
    auto ptr = stuSql::getinstance();
    info.username = ui->le_username->text();
    info.password = ui->le_password->text();
    info.auth = ui->le_auth->text();

    if(m_isAdd2)
    {
        ptr->AddUser(info);
    }
    else
    {
        info.username = m_info2.username;
        ptr->updateUser(info);
    }
    QMessageBox::information(nullptr,"信息","存储成功");
    this->hide();
}


void Dlg_AddUser::on_btn_cancel2_clicked()
{
    this->hide();
}

