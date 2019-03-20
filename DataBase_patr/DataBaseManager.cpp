#include "DataBaseManager.h"
#include <QCoreApplication>
#include <QDebug>
DataBaseManager::DataBaseManager()
{
    initDataBase();
    connectDataBase();
}

DataBaseManager::~DataBaseManager()
{
    closeDataBase();
}

/*!
  Override event function
  初始化数据库对象
*/
DBState DataBaseManager::initDataBase()
{
    sql_database = QSqlDatabase::addDatabase("QSQLITE");
}

/*!
  Override event function
  连接到数据库
*/
DBState DataBaseManager::connectDataBase()
{
    QString path = QCoreApplication::applicationDirPath();
    sql_database.setDatabaseName(path+"/UserDataBase.db");
    if (!sql_database.open())
    {
        qWarning() << "Error: Failed to connect database." << sql_database.lastError();
        return CONNECTERROR;
    }
    else
    {
        qInfo() << "Succeed to connect database." ;
        return NOERROR;
    }
}

/*!
  Override event function
  关闭数据库连接
*/
DBState DataBaseManager::closeDataBase()
{
    sql_database.close();
}

/*!
  Override event function
  创建数据库表
  colums sample:
    "Id_P int,LastName varchar(255),FirstName varchar(255),Address varchar(255),City varchar(255)"
*/
DBState DataBaseManager::createDataTable(QString tabelName, QString colums)
{
    sql_query = new QSqlQuery();
    QString sqlSentence = "create table if not exists "+ tabelName+"( "+colums+" )";
    qDebug()<<"创建新表的语句是："<<sqlSentence;
    if(!sql_query->exec(sqlSentence))
    {
        qWarning() << "Error: Fail to create table."<< sql_query->lastError();
    }
    else
    {
        qInfo() << "Table created!";
    }
    delete sql_query;
}

/*!
 * \brief DataBaseManager::insertData 向数据库插入数据
 * \param tableName
 * \param info
 * \return
 */
DBState DataBaseManager::insertUserData(UserInfo *userinfo)
{
    sql_query = new QSqlQuery();
    sql_query->prepare("INSERT INTO ExamineeInfo VALUES (:IP,:PORT,:NAME,:NUMBER,:TICKET)");
    sql_query->bindValue(":IP", userinfo->getUserIP());
    sql_query->bindValue(":PORT",userinfo->getUserPort());
    sql_query->bindValue(":NAME",userinfo->getUserName());
    sql_query->bindValue(":NUMBER",userinfo->getUserID());
    sql_query->bindValue(":TICKET",userinfo->getUserTicket());
    if(!sql_query->exec())
    {
        qWarning()<<sql_query->lastError();
        delete sql_query;
        return INFONOTEXIT;
    }
    else
    {
        delete sql_query;
        return NOERROR;
    }
}


/*!
  Override event function
  根据传递的sql语句查询信息
*/
DBState DataBaseManager::searchUserData( UserInfo *userinfo)
{
    sql_query = new QSqlQuery();
    sql_query->prepare("SELECT * FROM ExamineeInfo");
    if(!sql_query->exec())
    {
        qWarning()<<sql_query->lastError();
        return SQLERROR;
    }
    else
    {
        while (sql_query->next()) {
            QString Number = sql_query->value(3).toString();
            QString Ticket = sql_query->value(4).toString();
            if(Number ==QString::number( userinfo->getUserID()) && Ticket == userinfo->getUserTicket())
            {
                delete sql_query;
                return NOERROR;
            }
        }
        delete sql_query;
        return INFONOTEXIT;
    }

}
