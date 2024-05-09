#include "page_login.h"
#include "ui_page_login.h"
#include<QMessageBox>
#include <QSqlQuery>
#include<QDebug>
#include <QSqlDatabase>
#include <QKeyEvent>
Page_Login::Page_Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Page_Login)
    , u_ptrStuSql(nullptr)
{
    ui->setupUi(this);
}

Page_Login::~Page_Login()
{
    delete ui;
}

void Page_Login::on_btn_login_clicked()
{
    QString username = ui->le_user->text();
    strname = username;
    QString password = ui->le_password->text();
    QString sql=QString("select * from username where username='%1' and password='%2'")
                      .arg(username).arg(password);
    QSqlQuery query(sql);
    if(!query.next())
    {
        qDebug()<<"Login error";
        QMessageBox::information(this,"登录认证","登录失败,账户或者密码错误");
    }
    else
    {
        qDebug()<<"Login success";
        QMessageBox::information(this,"登录认证","登录成功");
        emit sendLoginSuccess();
        this->hide();
    }

}


void Page_Login::on_btn_exit_clicked()
{
    exit(0);
}

void Page_Login::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        on_btn_login_clicked();
    }
    QWidget::keyPressEvent(event);
}

