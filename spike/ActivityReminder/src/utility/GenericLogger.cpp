#include "GenericLogger.h"

//Log Processer Class
#include "LogProcesser.h"

namespace utility
{

std::string GenericLogger:: mFileName = "";
GenericLogger *GenericLogger::mGenericLogger = nullptr;

GenericLogger::GenericLogger(QObject *parent):
    QObject(parent),
    mLoggerThread(nullptr),
    mLogger(nullptr)
{
    mLoggerThread = new QThread(this);

    mLogger = new LogProcesser(mFileName, this);
    
    mLogger->moveToThread(mLoggerThread);

    mLoggerThread->start();

    connect(this, SIGNAL(requestToParseLoggerData(std::string)), mLogger, SLOT(parseLog(std::string)));
}

GenericLogger *GenericLogger::getLogger()
{
    return mGenericLogger;
}

void GenericLogger::setupLogger(std::string fileName)
{
    if(mGenericLogger == nullptr)
    {
        mFileName = fileName;
        mGenericLogger = new GenericLogger;
    }
}

void GenericLogger::logDebug(std::string message)
{
    log(message, DEBUG);
}

void GenericLogger::logInfo(std::string message)
{
    log(message, INFO);
}

void GenericLogger::logWarning(std::string message)
{
    log(message, WARNING);
}

void GenericLogger::logError(std::string message)
{
    log(message, ERROR);
}

void GenericLogger::log(std::string message, LOG_LEVEL logLevel)
{
    switch(logLevel)
    {
        case DEBUG:
            message = "DEBUG," + message;
            break;
        case INFO:
            message = "INFO," + message;
            break;
        case WARNING:
            message = "WARNING," + message;
            break;
        case ERROR:
            message = "ERROR," + message;
            break;
        default:
            message = "UNKNOWN," + message;
            break;
    }

    QMutexLocker locker(&mMutex);
    emit requestToParseLoggerData(message);
}

}
