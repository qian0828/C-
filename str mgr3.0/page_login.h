#ifndef PAGE_LOGIN_H
#define PAGE_LOGIN_H

#include <QWidget>
#include"stusql.h"
namespace Ui {
class Page_Login;
}

class Page_Login : public QWidget
{
    Q_OBJECT

public:
    explicit Page_Login(QWidget *parent = nullptr);
    ~Page_Login();

    QString strname;

    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_btn_login_clicked();

    void on_btn_exit_clicked();

signals:
    void sendLoginSuccess();
private:
    Ui::Page_Login *ui;

    stuSql *u_ptrStuSql;

};

#endif // PAGE_LOGIN_H
