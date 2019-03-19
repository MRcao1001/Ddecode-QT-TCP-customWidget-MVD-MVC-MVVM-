#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "DataModel/UserInfoModel.h"
#include "Public_part/log.h"
enum DBState{
    NOERROR = 0,
    CONNECTERROR = -1,
    INFONOTTRUE = -2,
    INFONOTEXIT = -3
};

class DataBaseManager
{
public:
    DataBaseManager();
    ~DataBaseManager();
    QSqlDatabase sql_database;
    QSqlQuery *sql_query;

public:
    /**
     * @brief initDataBase 初始化数据库
     */
    DBState initDataBase();
    /**
     * @brief connectDataBase 创建/打开/连接到数据库
     */
    DBState connectDataBase();
    /**
     * @brief closeDataBase 关闭数据库
     */
    DBState closeDataBase();
    /**
     * @brief createDataTable 创建表
     */
    DBState createDataTable(QString tabelName, QString colums);
    /**
     * @brief insertData 插入数据
     */
    DBState insertData(QString tableName, QString info);
    /**
     * @brief insertData 插入数据
     * @overload 传入用户数据模型插入
     */
    DBState insertData(QString tableName, UserInfoModel *userModel);
    /**
     * @brief updateData 更新数据
     */
    DBState updateData(QString tableName, QString oldInfo, QString newInfo, QString keyWord);
    /**
     * @brief searchData 查找用户信息数据
     */
    DBState searchData(QString SQL_Sentence);
    /**
     * @brief deleteData 删除数据
     */
    DBState deleteData(QString tableName, QString keyWord);
};

#endif // DATABASEMANAGER_H
