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
    qDebug()<<"\nSQL SENTENCE IS:"<<sqlSentence;
    if(!sql_query->exec(sqlSentence))
    {
        qWarning() << "\n Error: Fail to create table."<< sql_query->lastError();
    }
    else
    {
        qInfo() << "\n Table created!";
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
        delete sql_query;
        return SQLERROR;
    }
    else
    {
        while (sql_query->next()) {
            QString Number = sql_query->value(3).toString();
            QString Ticket = sql_query->value(4).toString();
            if(Number == userinfo->getUserID() && Ticket == userinfo->getUserTicket())
            {
                delete sql_query;
                return NOERROR;
            }
        }
        delete sql_query;
        return INFONOTEXIT;
    }

}
/**
 * @brief DataBaseManager::searchExamQuestionLib
 * @param examPaper
 * @return
 * 查找题库内所有的试题
 */
DBState DataBaseManager::searchExamQuestionLib(ExamPaperModel *examPaper)
{
    sql_query = new QSqlQuery();
    sql_query->prepare("SELECT * FROM ExamQuestionLib");
    if(!sql_query->exec())
    {
        qWarning()<<sql_query->lastError();
        delete sql_query;
        return SQLERROR;
    }
    else
    {
        while (sql_query->next()) {
            ExamChoiceQusetion *examQusetion = new ExamChoiceQusetion();
            if(sql_query->value(5).toString() == "FORBIDDEN")
            {
                continue;
            }
            examQusetion->setNumber(sql_query->value(0).toString().toInt());
            examQusetion->setScore(sql_query->value(1).toString());
            examQusetion->setTrueResult(sql_query->value(1).toString());
            examQusetion->setQuestion(sql_query->value(3).toString());
            QStringList DefultResult = sql_query->value(4).toString().split(',');
            if(DefultResult.count() != 4)
                return SQLERROR;
            examQusetion->setResultA(DefultResult.at(0));
            examQusetion->setResultB(DefultResult.at(1));
            examQusetion->setResultC(DefultResult.at(2));
            examQusetion->setResultD(DefultResult.at(3));
            examPaper->add(examQusetion);
        }
        delete sql_query;
        return NOERROR;
    }
}

DBState DataBaseManager::searchExamPaper(QStringList *ExamPaperList)
{
    sql_query = new QSqlQuery();
    sql_query->prepare("SELECT * FROM AllPaper");
    if(!sql_query->exec())
    {
        qWarning()<<sql_query->lastError();
        delete sql_query;
        return SQLERROR;
    }
    else
    {
        while (sql_query->next()) {

            QString result = sql_query->value(1).toString() +","+ sql_query->value(3).toString();
            ExamPaperList->append(result);
        }
        delete sql_query;
        return NOERROR;
    }
}

DBState DataBaseManager::searchExamPaperQuestion(QStringList *ExamPaperQuestionList, QString PaperName)
{
    sql_query = new QSqlQuery();
    sql_query->prepare("SELECT QUESTIONS FROM AllPaper WHERE NAME = :PaperName");
    sql_query->bindValue(":PaperName", PaperName);
    if(!sql_query->exec())
    {
        qWarning()<<sql_query->lastError();
        delete sql_query;
        return SQLERROR;
    }
    else
    {
        while (sql_query->next()) {
            *ExamPaperQuestionList = sql_query->value(0).toString().split(',');

        }
        delete sql_query;
        return NOERROR;
    }
}

DBState DataBaseManager::InsertNewPaper(ExamPaperModel *newPaperModel)
{
    sql_query = new QSqlQuery();
    sql_query->prepare("INSERT INTO AllPaper VALUES (NULL,:NAME,:QUESTIONS,:TIME)");
    QString QUESTIONS;
    QList<ExamChoiceQusetion* > examList = newPaperModel->getExamList();
    foreach(ExamChoiceQusetion *ecq, examList)
    {
        QUESTIONS += QString::number(ecq->getNumber());
        QUESTIONS += ",";
    }
    QUESTIONS = QUESTIONS.left(QUESTIONS.length()-1);
    if(newPaperModel->PaperName == "" || QUESTIONS == "" || newPaperModel->TotalTestTime=="")
    {
        delete  sql_query;
        return INFONOTTRUE;
    }
    sql_query->bindValue(":NAME", newPaperModel->PaperName);
    sql_query->bindValue(":QUESTIONS", QUESTIONS);
    sql_query->bindValue(":TIME", newPaperModel->TotalTestTime);

    if(!sql_query->exec())
    {
        qWarning()<<sql_query->lastError();
        delete sql_query;
        return SQLERROR;
    }
    delete sql_query;
    return NOERROR;
}

DBState DataBaseManager::InsertNewQuestion(ExamChoiceQusetion *newExamChoiceQuestion)
{
    sql_query = new QSqlQuery();
    sql_query->prepare("INSERT INTO ExamQuestionLib VALUES (NULL,:SCORE,:RESULT,:TEXT,:DEFULTRESULT)");
    QString DEFULTRESULT;
    DEFULTRESULT += newExamChoiceQuestion->getResultA() + ",";
    DEFULTRESULT += newExamChoiceQuestion->getResultB() + ",";
    DEFULTRESULT += newExamChoiceQuestion->getResultC() + ",";
    DEFULTRESULT += newExamChoiceQuestion->getResultD();
    if(newExamChoiceQuestion->getScore() == "" || newExamChoiceQuestion->getTrueResult() == "" || newExamChoiceQuestion->getQuestion()=="" || DEFULTRESULT == ",,,")
    {
        delete  sql_query;
        return INFONOTTRUE;
    }
    sql_query->bindValue(":SCORE", newExamChoiceQuestion->getScore());
    sql_query->bindValue(":RESULT",newExamChoiceQuestion->getTrueResult());
    sql_query->bindValue(":TEXT", newExamChoiceQuestion->getQuestion());
    sql_query->bindValue(":DEFULTRESULT", DEFULTRESULT);

    if(!sql_query->exec())
    {
        qWarning()<<sql_query->lastError();
        delete sql_query;
        return SQLERROR;
    }
    delete sql_query;
    return NOERROR;
}

DBState DataBaseManager::UpdataQuestion(ExamChoiceQusetion *examChoiceQuestion)
{
    sql_query = new QSqlQuery();
    sql_query->prepare("UPDATE ExamQuestionLib SET SCORE = :SCORE, RESULT = :RESULT, TEXT = :TEXT, DEFULTRESULT = :DEFULTRESULT WHERE ID = :ID");
    QString DEFULTRESULT;
    DEFULTRESULT += examChoiceQuestion->getResultA() + ",";
    DEFULTRESULT += examChoiceQuestion->getResultB() + ",";
    DEFULTRESULT += examChoiceQuestion->getResultC() + ",";
    DEFULTRESULT += examChoiceQuestion->getResultD();
    if(examChoiceQuestion->getScore() == "" || examChoiceQuestion->getTrueResult() == "" || examChoiceQuestion->getQuestion()=="" || DEFULTRESULT == ",,,")
    {
        delete  sql_query;
        return INFONOTTRUE;
    }
    sql_query->bindValue(":SCORE", examChoiceQuestion->getScore());
    sql_query->bindValue(":RESULT",examChoiceQuestion->getTrueResult());
    sql_query->bindValue(":TEXT", examChoiceQuestion->getQuestion());
    sql_query->bindValue(":DEFULTRESULT", DEFULTRESULT);
    sql_query->bindValue(":ID", examChoiceQuestion->getNumber());
    if(!sql_query->exec())
    {
        qWarning()<<sql_query->lastError();
        delete sql_query;
        return SQLERROR;
    }
    delete sql_query;
    return NOERROR;
}

DBState DataBaseManager::DeleteQuestion(ExamChoiceQusetion *examChoiceQuestion)
{
    sql_query = new QSqlQuery();
    sql_query->prepare("UPDATE ExamQuestionLib SET DELETED = :DELETED WHERE ID = :ID");
    sql_query->bindValue(":DELETED", "FORBIDDEN");
    sql_query->bindValue(":ID", examChoiceQuestion->getNumber());
    if(!sql_query->exec())
    {
        qWarning()<<sql_query->lastError();
        delete sql_query;
        return SQLERROR;
    }
    delete sql_query;
    return NOERROR;
}

DBState DataBaseManager::InsertNewExamHistory(QString Time, QString UserNumber, QString Score, QString Decision)
{
    sql_query = new QSqlQuery();
    sql_query->prepare("INSERT INTO ExamHistory VALUES (NULL,:TIME,:USERNUMBER,:SCORE,:DECISION)");
    if(Time == "" || UserNumber == "" || Score=="" || Decision == "")
    {
        delete  sql_query;
        return INFONOTTRUE;
    }
    sql_query->bindValue(":TIME", Time);
    sql_query->bindValue(":USERNUMBER", UserNumber);
    sql_query->bindValue(":SCORE", Score);
    sql_query->bindValue(":DECISION", Decision);

    if(!sql_query->exec())
    {
        qWarning()<<sql_query->lastError();
        delete sql_query;
        return SQLERROR;
    }
    delete sql_query;
    return NOERROR;
}

DBState DataBaseManager::GetExamHistory(QStringList &targetList, QString &UserNumber)
{
    sql_query = new QSqlQuery();
    sql_query->prepare("SELECT * FROM ExamHistory WHERE USERNUMBER = :USERNUMBER");
    sql_query->bindValue(":USERNUMBER", UserNumber);
    if(!sql_query->exec())
    {
        qWarning()<<sql_query->lastError();
        delete sql_query;
        return SQLERROR;
    }
    else
    {
        while (sql_query->next()) {
            QString Time = sql_query->value(1).toString();
            QString UserNumber = sql_query->value(2).toString();
            QString Score = sql_query->value(3).toString();
            QString Decision = sql_query->value(4).toString();
            targetList.append(Time+" "+UserNumber+" "+Score+" "+Decision);
        }
        delete sql_query;
        return NOERROR;
    }
}
