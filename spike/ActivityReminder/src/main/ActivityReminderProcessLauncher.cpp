#include "ActivityReminderProcessLauncher.h"

//Const & Utility
#include "ActivityReminderConst.h"
#include "GenericLogger.h"

#include <QCoreApplication>

ActivityReminderProcessLauncher::ActivityReminderProcessLauncher(QObject *parent):
    QObject(parent),
    mCoreProcess(nullptr),
    mUIProcess(nullptr),
    mDBProcess(nullptr)
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderProcessLauncher::ActivityReminderProcessLauncher");
}

int ActivityReminderProcessLauncher::init()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderProcessLauncher::init");

    //Starting CORE process
    mCoreProcess = new QProcess(this);

    connect(mCoreProcess, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(processStatusCore(QProcess::ProcessError)));
    connect(mCoreProcess, SIGNAL(finished(int)), this, SLOT(processExitedCore(int)));

    QString program = "ActivityReminderCoreApps";
    mCoreProcess->start(program);

    if(!mCoreProcess->waitForStarted())
    {
        return gActivityReminderConst::PROCESS_CORE_NOT_STARTED;
    }

    //Starting UI process
    mUIProcess = new QProcess(this);

    connect(mUIProcess, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(processStatusUi(QProcess::ProcessError)));
    connect(mUIProcess, SIGNAL(finished(int)), this, SLOT(processExitedUi(int)));

    program = "ActivityReminderUi";
    mUIProcess->start(program);

    if(!mUIProcess->waitForStarted())
    {
        return gActivityReminderConst::PROCESS_DB_NOT_STARTED;
    }

    //Starting DB process
    mDBProcess = new QProcess(this);

    connect(mDBProcess, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(processStatusDb(QProcess::ProcessError)));
    connect(mDBProcess, SIGNAL(finished(int)), this, SLOT(processExitedDb(int)));

    program = "ActivityReminderDB";
    mDBProcess->start(program);

    if(!mDBProcess->waitForStarted())
    {
        return gActivityReminderConst::PROCESS_DB_NOT_STARTED;
    }

    return gActivityReminderConst::SUCCESS;
}

void ActivityReminderProcessLauncher::end()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderProcessLauncher::end");
    if(mCoreProcess)
    {
        mCoreProcess->close();
    }

    if(mUIProcess)
    {
        mUIProcess->close();
    }

    if(mDBProcess)
    {
        mDBProcess->close();
    }
}

void ActivityReminderProcessLauncher::processStatusCore(QProcess::ProcessError errorStatus)
{
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderProcessLauncher::processStatusCore, error code:" + QString::number(errorStatus).toStdString());
}

void ActivityReminderProcessLauncher::processExitedCore(int exitCode)
{
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderProcessLauncher::processExitedCore, exit code:" + QString::number(exitCode).toStdString());
    closeAllProcess();
}

void ActivityReminderProcessLauncher::processStatusUi(QProcess::ProcessError errorStatus)
{
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderProcessLauncher::processStatusUi, error code:" + QString::number(errorStatus).toStdString());
}

void ActivityReminderProcessLauncher::processExitedUi(int exitCode)
{
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderProcessLauncher::processExitedUi, exit code:" + QString::number(exitCode).toStdString());
    closeAllProcess();
}

void ActivityReminderProcessLauncher::processStatusDb(QProcess::ProcessError errorStatus)
{
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderProcessLauncher::processStatusDb, error code:" + QString::number(errorStatus).toStdString());
}

void ActivityReminderProcessLauncher::processExitedDb(int exitCode)
{
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderProcessLauncher::processExitedDb, exit code:" + QString::number(exitCode).toStdString());
    closeAllProcess();
}

void ActivityReminderProcessLauncher::closeAllProcess()
{
    if(mCoreProcess->state() == QProcess::Running)
    {
        utility::GenericLogger::getLogger()->logInfo("ActivityReminderProcessLauncher::closeAllProcess, "
                                                     "closing CORE process");
        mCoreProcess->close();
    }

    //Do not close UI, will notify UI <TODO>
    /*
    if(mUIProcess->state() == QProcess::Running)
    {
        utility::GenericLogger::getLogger()->logInfo("ActivityReminderProcessLauncher::closeAllProcess, "
                                                     "closing UI process");
        mUIProcess->close();
    }*/

    if(mDBProcess->state() == QProcess::Running)
    {
        utility::GenericLogger::getLogger()->logInfo("ActivityReminderProcessLauncher::closeAllProcess, "
                                                     "closing DB process");
        mDBProcess->close();
        QCoreApplication::exit();
    }
}
