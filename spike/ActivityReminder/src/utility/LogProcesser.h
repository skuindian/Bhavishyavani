#ifndef LOGPROCESSER_H
#define LOGPROCESSER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QMutex>

#include <string>

namespace utility {

class LogProcesser : public QObject
{
    Q_OBJECT
public:
    explicit LogProcesser(std::string fileName, QObject *parent = nullptr);

private slots:
    void parseLog(std::string  log);

private:
    std::string mFileName;

    QFile logFile;
    QTextStream textStream;

    QMutex mLogMutex;
};

}
#endif // LOGPROCESSER_H
