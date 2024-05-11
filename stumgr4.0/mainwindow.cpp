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
#include<QHeaderView>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_ptrStuSql(nullptr)
{
    ui->setupUi(this);

    m_dlgLogin.show();
    auto f = [&](){
        //设置主窗口用户名显示
        ui->lb_username->setText(QString("用户名：%1").arg(m_dlgLogin.strname));
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


    //模拟数据：
    m_lNames<<"始秋白";
    m_lNames<<"孟双玉";
    m_lNames<<"鄞叶";
    m_lNames<<"丹问蕊";
    m_lNames<<"兴怡璐";
    m_lNames<<"汪昂杰";
    m_lNames<<"花意";
    m_lNames<<"诗载";
    m_lNames<<"公言文";
    m_lNames<<"泣雨竹";
    m_lNames<<"关代梅";
    m_lNames<<"印斯";
    m_lNames<<"鲍飞燕";
    m_lNames<<"度绮晴";
    m_lNames<<"冒寻梅";
    m_lNames<<"海鸿熙";
    m_lNames<<"帖华灿";
    m_lNames<<"倪鸿禧";
    m_lNames<<"卞涵蕾";
    m_lNames<<"少白";
    m_lNames<<"伦鹏海";
    m_lNames<<"贾景胜";
    m_lNames<<"栗彦灵";
    m_lNames<<"袁恬然";
    m_lNames<<"侯司";
    m_lNames<<"南门皎";
    m_lNames<<"泰婉静";
    m_lNames<<"叔琇芬";
    m_lNames<<"函嘉勋";
    m_lNames<<"穰海凡";
    m_lNames<<"祢倩秀";
    m_lNames<<"说英喆";
    m_lNames<<"淡端敏";
    m_lNames<<"骑绍祺";
    m_lNames<<"抗成周";
    m_lNames<<"运觅";
    m_lNames<<"帅开诚";
    m_lNames<<"邰骊茹";
    m_lNames<<"闾盈秀";
    m_lNames<<"费莫哲";
    m_lNames<<"殳能";
    m_lNames<<"仲淼淼";
    m_lNames<<"充念巧";
    m_lNames<<"厚新荣";
    m_lNames<<"邶力行";
    m_lNames<<"苌夏真";
    m_lNames<<"香怀曼";
    m_lNames<<"司徒海";
    m_lNames<<"戴雁荷";
    m_lNames<<"考绮晴";
    m_lNames<<"常清绮";
    m_lNames<<"骆凡儿";
    m_lNames<<"祭清霁";
    m_lNames<<"司空雅";
    m_lNames<<"福语海";
    m_lNames<<"申屠慕";
    m_lNames<<"汝正平";
    m_lNames<<"钞一瑾";
    m_lNames<<"枝文漪";
    m_lNames<<"刁从筠";
    m_lNames<<"信依玉";
    m_lNames<<"壬语海";
    m_lNames<<"高宣";
    m_lNames<<"龚念蕾";
    m_lNames<<"全清淑";
    m_lNames<<"章佳白";
    m_lNames<<"诺雪卉";
    m_lNames<<"岳雅柔";
    m_lNames<<"钟离雪";
    m_lNames<<"廖春柏";
    m_lNames<<"弥芷珊";
    m_lNames<<"畅骏逸";
    m_lNames<<"乙笑萍";
    m_lNames<<"错清妍";
    m_lNames<<"夔千凝";
    m_lNames<<"第以彤";
    m_lNames<<"梁瑶瑾";
    m_lNames<<"布雅韵";
    m_lNames<<"莱代秋";
    m_lNames<<"晋木";
    m_lNames<<"机小雯";
    m_lNames<<"习捷";
    m_lNames<<"巩琳怡";
    m_lNames<<"纪绿旋";
    m_lNames<<"扬涵易";
    m_lNames<<"野婷美";
    m_lNames<<"第漫";
    m_lNames<<"丰桐欣";
    m_lNames<<"暨怡月";
    m_lNames<<"友新颖";
    m_lNames<<"席琳溪";
    m_lNames<<"税芬菲";
    m_lNames<<"家惜蕊";
    m_lNames<<"塞问风";

    qDebug()<<m_dlgLogin.strname;
    updateTable();
    updateTable2();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//切换学生管理界面和管理员管理界面
void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
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

//模拟学生数据
void MainWindow::on_btn_simulation_clicked()
{
    QRandomGenerator g,c;
    g.seed(0);
    c.seed(0);
    for(int i=0;i<m_lNames.size();i++)
    {
        auto grade = g.bounded(7,10);
        auto uiclass = c.bounded(1,9);
        StuInfo info;
        info.name = m_lNames[i];
        if(i%3){
            info.age = 16;
        }
        if(i%7){
            info.age = 17;
        }
        if(i%2){
            info.age = 18;
        }

        info.grade = grade;
        info.uiclass = uiclass;
        info.studentid = i+1;
        info.phone = "13812345678";
        info.address = "天津市津南区同砚路38号";
        m_ptrStuSql->addStu(info);
    }

    updateTable();
}


void MainWindow::on_btn_add_clicked()
{
    if(ifHaveAuth() == 0)
    {
        QMessageBox::information(nullptr,"警告","无权限");
        return;
    }
    m_dlgAddStu.setType(true);
    m_dlgAddStu.exec();
    updateTable();
}


void MainWindow::on_btn_clear_clicked()
{
    if(!ifHaveAuth())
    {
        QMessageBox::information(nullptr,"警告","无权限");
        return;
    }
    m_ptrStuSql->clearStuTable();
    updateTable();
}

void MainWindow::updateTable()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(8);
    QStringList l;
    l<<"id"<<"姓名"<<"年龄"<<"年级"<<"班级"<<"学号"<<"电话"<<"地址";
    ui->tableWidget->setHorizontalHeaderLabels(l);

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnWidth(0,50);
    ui->tableWidget->setColumnWidth(2,50);
    ui->tableWidget->setColumnWidth(3,50);
    ui->tableWidget->setColumnWidth(4,50);
    ui->tableWidget->setColumnWidth(7,200);

    auto cnt = m_ptrStuSql->getStuCnt();
    ui->lb_cnt->setText(QString("数量:%1").arg(cnt));
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
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(lStudents[i].address));
    }
}

//更新用户表
void MainWindow::updateTable2()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setColumnCount(3);
    QStringList l;
    l<<"用户名(不可修改)"<<"密码"<<"权限";
    ui->tableWidget_2->setHorizontalHeaderLabels(l);

    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setColumnWidth(0,125);
    ui->tableWidget_2->setColumnWidth(1,150);

    auto cnt = m_ptrStuSql->getUserCnt();
    ui->lb_cnt2->setText(QString("数量:%1").arg(cnt));
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
    if(!ifHaveAuth())
    {
        QMessageBox::information(nullptr,"警告","无权限");
        return;
    }
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
    if(!ifHaveAuth())
    {
        QMessageBox::information(nullptr,"警告","无权限");
        return;
    }
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
        info.address = ui->tableWidget->item(i,7)->text();

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
    l<<"id"<<"姓名"<<"年龄"<<"年级"<<"班级"<<"学号"<<"电话"<<"地址";
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
        ui->tableWidget->setItem(index,7,new QTableWidgetItem(lStudents[i].address));
        index++;
    }
    ui->tableWidget->setRowCount(index);
}




void MainWindow::on_btn_add2_clicked()
{
    if(!ifHaveAuth())
    {
        QMessageBox::information(nullptr,"警告","无权限");
        return;
    }
    m_dlgAddUser.setType2(true);
    m_dlgAddUser.exec();
    updateTable2();
}


void MainWindow::on_btn_del2_clicked()
{
    if(!ifHaveAuth())
    {
        QMessageBox::information(nullptr,"警告","无权限");
        return;
    }
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
    if(!ifHaveAuth())
    {
        QMessageBox::information(nullptr,"警告","无权限");
        return;
    }
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
    QString strFilter2 = ui->le_search2->text();
    if(strFilter2.isEmpty())
    {
        // QMessageBox::information(nullptr,"警告","搜索为空");
        updateTable2();
        return;
    }

    ui->tableWidget_2->clear();
    ui->tableWidget_2->setColumnCount(3);
    QStringList l;
    l<<"用户名"<<"密码"<<"权限";
    ui->tableWidget_2->setHorizontalHeaderLabels(l);

    auto cnt = m_ptrStuSql->getUserCnt();
    ui->lb_cnt2->setText(QString("数量:%1").arg(cnt));
    QList<UserInfo> lUsers = m_ptrStuSql->getPageUser(0,cnt);


    int index = 0;
    for(int i=0;i<lUsers.size();i++)
    {
        if(!lUsers[i].username.contains(strFilter2))
        {
            continue;
        }



        // ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        ui->tableWidget_2->setItem(index,0,new QTableWidgetItem(lUsers[i].username));
        ui->tableWidget_2->setItem(index,1,new QTableWidgetItem(lUsers[i].password));
        ui->tableWidget_2->setItem(index,2,new QTableWidgetItem(lUsers[i].auth));
        index++;
    }
    ui->tableWidget_2->setRowCount(index);
}

// void MainWindow::Noauth()
// {
//     if(!ifHaveAuth())
//     {
//         QMessageBox::information(nullptr,"警告","无权限");
//     }
// }

bool MainWindow::ifHaveAuth()
{
    QString strusername = m_dlgLogin.strname;
    QString textToSearchFor = strusername;
    QPair<int, int> position = findItemInTableWidget(ui->tableWidget_2, textToSearchFor);
    int row = position.first;
    // int column = position.second;
    QTableWidgetItem *strau = ui->tableWidget_2->item(row,2);
    QString strauth = strau->text();
    if(strauth == "admin")
    {
        return true;
    }
    if(strauth == "onlyread")
    {
        return false;
    }
}

QPair<int, int> MainWindow::findItemInTableWidget(QTableWidget *tableWidget, const QString &textToFind)
{
    int rows = tableWidget->rowCount();
    int columns = tableWidget->columnCount();

    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            QTableWidgetItem *item = tableWidget->item(row, column);
            if (item != nullptr && item->text() == textToFind) {
                // 找到匹配的项，返回行和列索引
                return QPair<int, int>(row, column);
            }
        }
    }
    // // 如果没有找到匹配的项，返回 -1, -1
    // return QPair<int, int>(-1, -1);
}

//按回车搜索
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        on_btn_search_clicked();
        on_btn_search2_clicked();
    }
    QWidget::keyPressEvent(event);
}


