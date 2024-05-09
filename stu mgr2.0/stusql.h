#ifndef STUSQL_H
#define STUSQL_H

#include <QObject>
#include <QSqlDatabase>
struct StuInfo
{
    int id;
    QString name;
    quint8 age;
    quint16 grade;
    quint16 uiclass;
    quint32 studentid;
    QString phone;
    QString wechat;
};
struct UserInfo
{
    QString username;
    QString password;
    QString auth;
};

class stuSql : public QObject
{
    Q_OBJECT
public:
    static stuSql * ptrstuSql;
    static stuSql *getinstance()
    {
        if(nullptr == ptrstuSql)
        {
            ptrstuSql = new stuSql;
        }
        return ptrstuSql;
    }

    explicit stuSql(QObject *parent = nullptr);

    void init();

    //统计总数
    quint32 getStuCnt();

    quint32 getUserCnt();
    //查询学生
    QList<StuInfo> getPageStu(quint32 page,quint32 uiCnt);

    //增加学生
    bool addStu(StuInfo info);

    //删除学生
    bool delStu(int id);

    //清空学生
    bool clearStuTable();

    //修改学生
    bool UpdateStuInfo(StuInfo info);

    //查询用户
    QList<UserInfo> getPageUser(quint32 page,quint32 uiCnt);

    //查询用户
    bool isExist(QString strUser);

    //修改用户
    bool updateUser(UserInfo info);

    //添加用户
    bool AddUser(UserInfo info);

    //删除用户
    bool delUser(QString strUserName);

signals:

private:
    QSqlDatabase m_db;
};

#endif // STUSQL_H
