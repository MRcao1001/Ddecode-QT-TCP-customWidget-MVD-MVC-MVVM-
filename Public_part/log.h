#pragma once
#include <QString>
#include <QMutex>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QDir>
#include <QDateTime>
static QString logDirectory;
static QString logFileName;
static QMutex mutex;
static QFile file;
static QTextStream textStream;

#define GLOG( FUNC )   {if ((status = FUNC) != kOK)                 \
                            {                                       \
                                qWarning() << "[ERROR]:" << status; \
                                return status;                       \
                            }                                       \
                            else                                    \
                            {                                       \
                                qInfo() << "[SUCCESS]";             \
                            }}

#define LOG(FUNC)      {if (FUNC)                                   \
                            {                                       \
                                qInfo() << "[SUCCESS]";             \
                            }                                       \
                            else                                    \
                            {                                       \
                                qFatal() << "[ERROR]";              \
                            }}


#define RLOG(FUNC)       {if (int status = FUNC == OK)              \
                            {                                       \
                                qInfo() << "[SUCCESS]";             \
                            }                                       \
                            else                                    \
                            {                                       \
                                qWarning() << "[ERROR]:" << status; \
                                return status;                       \
                            }}

#define DBLOG(FUNC1,FUNC2) {if (FUNC1)                              \
                            {                                       \
                                qInfo() << "[SUCCESS]";             \
                            }                                       \
                            else                                    \
                            {                                       \
                                qWarning() << "[ERROR]:" << FUNC2;  \
                            }}

#define RDBLOG(FUNC1,FUNC2) {if (FUNC1)                             \
                            {                                       \
                                qInfo() << "[SUCCESS]";             \
                            }                                       \
                            else                                    \
                            {                                       \
                                qWarning() << "[ERROR]:" << FUNC2;  \
                                return DB_EXEC;                      \
                            }}


void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);

