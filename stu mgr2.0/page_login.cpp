#include "page_login.h"
#include "ui_page_login.h"

Page_Login::Page_Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Page_Login)
{
    ui->setupUi(this);
}

Page_Login::~Page_Login()
{
    delete ui;
}

void Page_Login::on_btn_login_clicked()
{
    emit sendLoginSuccess();
    this->hide();
}


void Page_Login::on_btn_exit_clicked()
{
    exit(0);
}

