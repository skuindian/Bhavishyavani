#ifndef ACTIVITYREMINDERPROCESSLAUNCHER_H
#define ACTIVITYREMINDERPROCESSLAUNCHER_H

#include <QObject>
#include <QProcess>

class ActivityReminderProcessLauncher: public QObject
{
    Q_OBJECT

public:
    ActivityReminderProcessLauncher(QObject *parent = 0);

    int init();
    void end();

private:
    QProcess *mCoreProcess;
    QProcess *mUIProcess;
    QProcess *mDBProcess;

    void closeAllProcess();

public slots:
    void processExitedCore(int exitCode);
    void processStatusCore(QProcess::ProcessError errorStatus);
    void processExitedUi(int exitCode);
    void processStatusUi(QProcess::ProcessError errorStatus);
    void processExitedDb(int exitCode);
    void processStatusDb(QProcess::ProcessError errorStatus);
};

#endif // ACTIVITYREMINDERPROCESSLAUNCHER_H
