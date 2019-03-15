#include "log.h"

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    logDirectory  = QApplication::applicationDirPath() + "/Log/";
    QDir dir(logDirectory);
    if(!dir.exists())
        dir.mkdir(logDirectory);
    logFileName = logDirectory + (QApplication::applicationName()+".LogInfo");

    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("[Debug]");
        break;
    case QtInfoMsg:
        text = QString("[Info]");
        break;
    case QtWarningMsg:
        text = QString("[Warning]");
        break;
    case QtCriticalMsg:
        text = QString("[Critical]");
        break;
    case QtFatalMsg:
        text = QString("[Fatal]");
    }
    text.append(QString("[%1]").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
    text.append(QString("[%1: Line: %2]").arg(QString(context.file)).arg(context.line));
    text.append(QString("[Function: %1]").arg(QString(context.function)));

    mutex.lock();
    file.setFileName(logFileName);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    textStream.setDevice(&file);
    textStream << text << QString("Message: %1").arg(msg) << endl;
    file.close();
    mutex.unlock();
}
