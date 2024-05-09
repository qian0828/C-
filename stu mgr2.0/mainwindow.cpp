#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "page_login.h"
#include "ui_page_login.h"
#include<QMessageBox>
#include <QCoreApplication>
#include <QFile>
#include <QKeyEvent>
#include<QRandomGenerator>
#include<QTreeWidget>
#include<QStackedWidget>
#include <QSqlQuery>
#include <QSqlDatabase>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_ptrStuSql(nullptr)
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


    m_ptrStuSql = stuSql::getinstance();
    m_ptrStuSql->init();

    updateTable();
    updateTable2();
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

void MainWindow::on_btn_exit_clicked()
{
    exit(0);
}


void MainWindow::on_btn_add_clicked()
{
    m_dlgAddStu.setType(true);
    m_dlgAddStu.exec();
    updateTable();
}


void MainWindow::on_btn_clear_clicked()
{
    m_ptrStuSql->clearStuTable();
    updateTable();
}

void MainWindow::updateTable()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(8);
    QStringList l;
    l<<"id"<<"姓名"<<"年龄"<<"年级"<<"班级"<<"学号"<<"电话"<<"微信";
    ui->tableWidget->setHorizontalHeaderLabels(l);

    auto cnt = m_ptrStuSql->getStuCnt();
    QList<StuInfo> lStudents = m_ptrStuSql->getPageStu(0,cnt);

    ui->tableWidget->setRowCount(cnt);
    for(int i=0;i<lStudents.size();i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(lStudents[i].id)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(lStudents[i].name));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(lStudents[i].age)));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(lStudents[i].grade)));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(lStudents[i].uiclass)));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(lStudents[i].studentid)));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(lStudents[i].phone));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(lStudents[i].wechat));
    }
}

void MainWindow::updateTable2()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setColumnCount(3);
    QStringList l;
    l<<"用户名"<<"密码"<<"权限";
    ui->tableWidget_2->setHorizontalHeaderLabels(l);

    auto cnt = m_ptrStuSql->getUserCnt();
    QList<UserInfo> lUsers = m_ptrStuSql->getPageUser(0,cnt);

    ui->tableWidget_2->setRowCount(cnt);
    for(int i=0;i<lUsers.size();i++)
    {
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(lUsers[i].username));
        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(lUsers[i].password));
        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(lUsers[i].auth));
    }
}


void MainWindow::on_btn_del_clicked()
{
    int i = ui->tableWidget->currentRow();
    if(i>=0)
    {
        int id = ui->tableWidget->item(i,0)->text().toUInt();
        m_ptrStuSql->delStu(id);
        updateTable();
        QMessageBox::information(nullptr,"信息","删除成功");
    }

}


void MainWindow::on_btn_update_clicked()
{
    StuInfo info;
    int i = ui->tableWidget->currentRow();
    if(i>=0)
    {
        info.id = ui->tableWidget->item(i,0)->text().toUInt();
        info.name = ui->tableWidget->item(i,1)->text();
        info.age = ui->tableWidget->item(i,2)->text().toUInt();
        info.grade = ui->tableWidget->item(i,3)->text().toUInt();
        info.uiclass = ui->tableWidget->item(i,4)->text().toUInt();
        info.studentid = ui->tableWidget->item(i,5)->text().toUInt();
        info.phone = ui->tableWidget->item(i,6)->text();
        info.wechat = ui->tableWidget->item(i,7)->text();

        m_dlgAddStu.setType(false,info);
        m_dlgAddStu.exec();
    }

    updateTable();
}


void MainWindow::on_btn_search_clicked()
{
    QString strFilter = ui->le_search->text();
    if(strFilter.isEmpty())
    {
        // QMessageBox::information(nullptr,"警告","搜索为空");
        updateTable();
        return;
    }

    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(8);
    QStringList l;
    l<<"id"<<"姓名"<<"年龄"<<"年级"<<"班级"<<"学号"<<"电话"<<"微信";
    ui->tableWidget->setHorizontalHeaderLabels(l);

    auto cnt = m_ptrStuSql->getStuCnt();
    ui->lb_cnt->setText(QString("数量:%1").arg(cnt));
    QList<StuInfo> lStudents = m_ptrStuSql->getPageStu(0,cnt);


    int index = 0;
    for(int i=0;i<lStudents.size();i++)
    {
        if(!lStudents[i].name.contains(strFilter))
        {
            continue;
        }



        // ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        ui->tableWidget->setItem(index,0,new QTableWidgetItem(QString::number(lStudents[i].id)));
        ui->tableWidget->setItem(index,1,new QTableWidgetItem(lStudents[i].name));
        ui->tableWidget->setItem(index,2,new QTableWidgetItem(QString::number(lStudents[i].age)));
        ui->tableWidget->setItem(index,3,new QTableWidgetItem(QString::number(lStudents[i].grade)));
        ui->tableWidget->setItem(index,4,new QTableWidgetItem(QString::number(lStudents[i].uiclass)));
        ui->tableWidget->setItem(index,5,new QTableWidgetItem(QString::number(lStudents[i].studentid)));
        ui->tableWidget->setItem(index,6,new QTableWidgetItem(lStudents[i].phone));
        ui->tableWidget->setItem(index,7,new QTableWidgetItem(lStudents[i].wechat));
        index++;
    }
    ui->tableWidget->setRowCount(index);
}




void MainWindow::on_btn_add2_clicked()
{
    m_dlgAddUser.setType2(true);
    m_dlgAddUser.exec();
    updateTable2();
}


void MainWindow::on_btn_del2_clicked()
{
    int i = ui->tableWidget_2->currentRow();
    if(i>=0)
    {
        QString username = ui->tableWidget_2->item(i,0)->text();
        m_ptrStuSql->delUser(username);
        updateTable2();
        QMessageBox::information(nullptr,"信息","删除成功");
    }

}


void MainWindow::on_btn_update2_clicked()
{
    UserInfo info;
    int i = ui->tableWidget_2->currentRow();
    if(i>=0)
    {
        info.username = ui->tableWidget_2->item(i,0)->text();
        info.password = ui->tableWidget_2->item(i,1)->text();
        info.auth = ui->tableWidget_2->item(i,2)->text();

        m_dlgAddUser.setType2(false,info);
        m_dlgAddUser.exec();
    }

    updateTable2();
}


void MainWindow::on_btn_search2_clicked()
{

}


