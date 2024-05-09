#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "page_login.h"
#include<dlg_addstu.h>
#include<dlg_adduser.h>
#include <QMainWindow>
#include<QTreeWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_btn_add2_clicked();

    void on_btn_update2_clicked();


    void on_btn_exit_clicked();

    void on_btn_add_clicked();

    void on_btn_update_clicked();

private:
    Ui::MainWindow *ui;

    Page_Login m_dlgLogin;

    Dlg_AddStu m_dlgAddStu;

    Dlg_AddUser m_dlgAddUser;
};
#endif // MAINWINDOW_H
