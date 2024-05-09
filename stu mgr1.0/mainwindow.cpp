#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "page_login.h"
#include<QTreeWidget>
#include<QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_dlgLogin.show();
    auto f = [&](){
        this->show();
    };
    connect(&m_dlgLogin,&Page_Login::sendLoginSuccess,this,f);

    ui->treeWidget->clear();

    QStringList l;
    l<<"学生信息管理系统";
    QTreeWidgetItem *pf = new QTreeWidgetItem(ui->treeWidget,l);
    ui->treeWidget->addTopLevelItem(pf);
    l.clear();
    l<<"学生管理";
    QTreeWidgetItem *p1=new QTreeWidgetItem(pf,l);
    l.clear();
    l<<"管理员管理";
    QTreeWidgetItem *p2=new QTreeWidgetItem(pf,l);
    pf->addChild(p1);
    pf->addChild(p2);

    ui->treeWidget->expandAll();
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    //QString curItem_text = item->text(column);
    if(item->text(column) == "学生管理")
    {
        ui->stackedWidget->setCurrentWidget(ui->page);
    }
    else if(item->text(column) == "管理员管理")
    {
        ui->stackedWidget->setCurrentWidget(ui->page_2);
    }

}

void MainWindow::on_btn_add_clicked()
{
    m_dlgAddStu.setType(true);
    m_dlgAddStu.exec();
}

void MainWindow::on_btn_update_clicked()
{
    StuInfo info;
    m_dlgAddStu.setType(false,info);
    m_dlgAddStu.exec();
}

void MainWindow::on_btn_add2_clicked()
{
    m_dlgAddUser.setType2(true);
    m_dlgAddUser.exec();

}

void MainWindow::on_btn_update2_clicked()
{
    UserInfo info;
    m_dlgAddUser.setType2(false,info);
    m_dlgAddUser.exec();

}


void MainWindow::on_btn_exit_clicked()
{
    exit(0);
}







