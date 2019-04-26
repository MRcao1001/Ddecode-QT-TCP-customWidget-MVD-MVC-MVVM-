#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "DataModeView/UserInfo.h"
#include "Public_part/log.h"
enum DBState{
    NOERROR = 0,
    CONNECTERROR = -1,
    INFONOTTRUE = -2,
    INFONOTEXIT = -3,
    SQLERROR = -4,
};

class DataBaseManager
{
public:
    DataBaseManager();
    ~DataBaseManager();
    QSqlDatabase sql_database;
    QSqlQuery *sql_query;
    QString userTable = "ExamineeInfo";

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
    DBState insertUserData(UserInfo *userinfo = nullptr);
    /**
     * @brief updateData 更新数据
     */
    DBState updateData(QString tableName, QString oldInfo, QString newInfo, QString keyWord);
    /**
     * @brief searchData 查找用户信息数据
     */
    DBState searchUserData(UserInfo *userinfo = nullptr);
    /**
     * @brief searchExamQuestionLib 查找题库内所有的试题
     * @param examPaper
     * @return
     */
    DBState searchExamQuestionLib(ExamPaperModel *examPaper);
    /**
     * @brief deleteData 删除数据
     */
    DBState deleteData(QString tableName, QString keyWord);
};

#endif // DATABASEMANAGER_H
