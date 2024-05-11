#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"stusql.h"
#include "ui_page_login.h"
#include <QMainWindow>
#include"page_login.h"
#include<dlg_addstu.h>
#include<dlg_adduser.h>
#include<QTreeWidget>
#include<QTableWidget>
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

    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_btn_exit_clicked();

    void on_btn_simulation_clicked();

    void on_btn_add_clicked();

    void on_btn_clear_clicked();

    void on_btn_del_clicked();

    void on_btn_update_clicked();

    void on_btn_search_clicked();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_btn_add2_clicked();

    void on_btn_del2_clicked();

    void on_btn_update2_clicked();

    void on_btn_search2_clicked();

    bool ifHaveAuth();

    QPair<int, int> findItemInTableWidget(QTableWidget *tableWidget, const QString &textToFind);
private:
    Ui::MainWindow *ui;

    Page_Login m_dlgLogin;

    stuSql *m_ptrStuSql;

    QStringList m_lNames;

    Dlg_AddStu m_dlgAddStu;

    Dlg_AddUser m_dlgAddUser;

    void updateTable();

    void updateTable2();

};
#endif // MAINWINDOW_H
