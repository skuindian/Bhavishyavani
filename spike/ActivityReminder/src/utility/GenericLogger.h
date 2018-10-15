#ifndef GENERICLOGGER_H
#define GENERICLOGGER_H

#include "string"
#include "queue"

#include <QThread>

#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>

namespace utility {

typedef enum
{
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR
}LOG_LEVEL;

class LogProcesser;
class GenericLogger: public QObject
{
    Q_OBJECT

public:
    static GenericLogger *getLogger();
    static void setupLogger(std::string fileName);

    void logDebug(std::string message);
    void logInfo(std::string message);
    void logWarning(std::string message);
    void logError(std::string message);

private:
    GenericLogger(QObject *parent = nullptr);
    static GenericLogger *mGenericLogger;

    QThread *mLoggerThread;

    LogProcesser *mLogger;

    QMutex mMutex;

    QWaitCondition mProcessLog;

    static std::string mFileName;

    //Methods
    void log(std::string message, LOG_LEVEL logLevel);

signals:
    void requestToParseLoggerData(std::string);
};
}

#endif // GENERICLOGGER_H
