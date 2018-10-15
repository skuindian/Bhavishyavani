#include "LogProcesser.h"

#include <ctime>

#include <QDir>

namespace utility {

LogProcesser::LogProcesser(std::string fileName, QObject *parent) : QObject(parent)
{
    //Crete directory if not exists
    if(!QDir("logs").exists())
    {
        QDir().mkdir("logs");
    }

    mFileName = "logs/" + fileName;

    logFile.setFileName(mFileName.c_str());
    textStream.setDevice(&logFile);
}

void LogProcesser::parseLog(std::string log)
{
    QMutexLocker locker(&mLogMutex);

    if(logFile.open(QIODevice::Append | QIODevice::Text))
    {
        time_t now = time(0);
        tm *currentTime = localtime(&now);

        QString dateTimeStr = QString::number(1900 + currentTime->tm_year) + "-" +
                              QString::number(currentTime->tm_mon) + "-" +
                              QString::number(currentTime->tm_mday) + "," +
                              QString::number(currentTime->tm_hour) + ":" +
                              QString::number(currentTime->tm_min) + ":" +
                              QString::number(currentTime->tm_sec) + ",";

        log = dateTimeStr.toStdString() + log;

        textStream << log.c_str();
        textStream << "\n";

        logFile.close();
    }
}
}
