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
    if(!sql_query->exec("create table if not exists"+ tabelName+"("+colums+")"))
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
  Override event function
  查询用户信息,并判断是否存在,同时设置用户数据模型
*/
DBState DataBaseManager::searchData(UserInfoModel *userModel,QString tableName, QString userName, QString userPassword)
{
    sql_query = new QSqlQuery();
    QString sqlSentence = "select * from "+tableName+" where Name = "+"'"+userName+"';";
    sql_query->exec(sqlSentence);
    if(!sql_query->exec())
    {
        qWarning()<<sql_query->lastError();
        return INFONOTEXIT;
    }
    else
    {
        while(sql_query->next())
        {
            QString Password = sql_query->value(2).toString();
            if(Password == userPassword)
            {
//                if(userModel != nullptr)
//                {
//                    userModel->InitModel(sql_query->value(0).toString(),sql_query->value(1).toString(),sql_query->value(2).toString());
//                }
                return NOERROR;
            }
            else {
                return INFONOTTRUE;
            }
        }
    }
    delete sql_query;
}
