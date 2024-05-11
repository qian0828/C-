#include "stusql.h"
#include<QMessageBox>
#include<QCoreApplication>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include <QSqlError>

stuSql * stuSql::ptrstuSql = nullptr;
stuSql::stuSql(QObject *parent)
    : QObject{parent}
{

}

void stuSql::init()
{
    if(QSqlDatabase::drivers().isEmpty())
        qDebug()<<"No database drivers found";

    m_db = QSqlDatabase::addDatabase("QSQLITE");
#if 1
    auto str = QCoreApplication::applicationDirPath()+"/data.db";
    qDebug()<<str;
#endif
//  str = "D:\\data.db";
    m_db.setDatabaseName(str); //str为data.db文件路径
    if(!m_db.open())
        qDebug()<<"db not open";
}

quint32 stuSql::getStuCnt()
{
    QSqlQuery sql(m_db);
    sql.exec("select count(id) from student");
    quint32 uiCnt = 0;
    while(sql.next())
    {
        uiCnt = sql.value(0).toUInt();
    }
    return uiCnt;
}

quint32 stuSql::getUserCnt()
{
    QSqlQuery sql(m_db);
    sql.exec("select count(username) from username");
    quint32 uiCnt = 0;
    while(sql.next())
    {
        uiCnt = sql.value(0).toUInt();
    }
    return uiCnt;
}

QList<StuInfo> stuSql::getPageStu(quint32 page, quint32 uiCnt)
{
    QList<StuInfo> l;
    QSqlQuery sql(m_db);
    QString strsql = QString("select * from student order by id limit %1 offset %2").
            arg(uiCnt).arg(page*uiCnt);
    sql.exec(strsql);
    StuInfo info;
    while(sql.next())
    {
        info.id = sql.value(0).toUInt();
        info.name = sql.value(1).toString();
        info.age = sql.value(2).toUInt();
        info.grade = sql.value(3).toUInt();
        info.uiclass = sql.value(4).toUInt();
        info.studentid = sql.value(5).toUInt();
        info.phone = sql.value(6).toString();
        info.address = sql.value(7).toString();
        l.push_back(info);
    }
    return l;
}

bool stuSql::addStu(StuInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("insert into student values(null,'%1',%2,%3,%4,%5,'%6','%7')").
            arg(info.name).
            arg(info.age).
            arg(info.grade).
            arg(info.uiclass).
            arg(info.studentid).
            arg(info.phone).
            arg(info.address);
    return sql.exec(strSql);
}

bool stuSql::delStu(int id)
{
    QSqlQuery sql(m_db);
    return sql.exec(QString("delete from student where id = %1").arg(id));
}

bool stuSql::clearStuTable()
{
    QSqlQuery sql(m_db);
    sql.exec("delete from student");
    return sql.exec("delete from sqlite_sequence where name ='student'");

}

bool stuSql::UpdateStuInfo(StuInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("update student set name='%1',age=%2,grade=%3,class=%4,studentid=%5,"
                             "phone='%6',wechat='%7' where id=%8").
                     arg(info.name).
                     arg(info.age).
                     arg(info.grade).
                     arg(info.uiclass).
                     arg(info.studentid).
                     arg(info.phone).
                     arg(info.address).arg(info.id);
    return sql.exec(strSql);
}

QList<UserInfo> stuSql::getPageUser(quint32 page,quint32 uiCnt)
{
    QList<UserInfo> l;
    QSqlQuery sql(m_db);
    QString strsql = QString("select * from username order by username limit %1 offset %2").
                     arg(uiCnt).arg(page*uiCnt);
    sql.exec(strsql);
    UserInfo info;
    while(sql.next())
    {
        info.username = sql.value(0).toString();
        info.password = sql.value(1).toString();
        info.auth = sql.value(2).toString();
        l.push_back(info);
    }
    return l;
}

bool stuSql::isExist(QString strUser)
{
    QSqlQuery sql(m_db);
    sql.exec(QString("select *from username where username='%1'").arg(strUser));
    return sql.next();
}

bool stuSql::updateUser(UserInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("update username set password='%1',auth='%2' where username='%3'").
                     arg(info.password).
                     arg(info.auth).
                     arg(info.username);
    return sql.exec(strSql);
}

bool stuSql::AddUser(UserInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("insert into username values('%1','%2','%3')").
                     arg(info.username).
                     arg(info.password).
                     arg(info.auth);
    return sql.exec(strSql);
}

bool stuSql::delUser(QString strUserName)
{
    QSqlQuery sql(m_db);
    return sql.exec(QString("delete from username where username='%1'").arg(strUserName));
}

