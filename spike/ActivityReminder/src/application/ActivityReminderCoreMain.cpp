#include "ActivityReminderCoreMain.h"

#include "ActivityReminderConst.h"
#include "GenericLogger.h"

#include "ActivityReminderUIConnector.h"
#include "ActivityReminderDBConnector.h"

ActivityReminderCoreMain::ActivityReminderCoreMain(QObject *parent) :
    QObject(parent),
    mActivityReminderUIConnector(nullptr)
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderCoreMain::ActivityReminderCoreMain");
}

ActivityReminderCoreMain::~ActivityReminderCoreMain()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderCoreMain::~ActivityReminderCoreMain");
}

int ActivityReminderCoreMain::init()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderCoreMain::init");
    int conStatus;

    mActivityReminderUIConnector = new ActivityReminderUIConnector(this);
    conStatus = mActivityReminderUIConnector->init();

    utility::GenericLogger::getLogger()->logInfo("ActivityReminderCoreMain::init, UI conStatus:" + QString::number(conStatus).toStdString());

    if(conStatus != gActivityReminderConst::SUCCESS)
    {
        return conStatus;
    }

    mActivityReminderDBConnector = new ActivityReminderDBConnector(this);
    conStatus = mActivityReminderDBConnector->init();
    if(conStatus != gActivityReminderConst::SUCCESS)
    {
        return conStatus;
    }

    //Define all the signal/slot
    connect(mActivityReminderUIConnector, SIGNAL(processRecivedDataFromUI(QString)),
            this, SLOT(processRecivedDataToSaveIntoDB(QString)));
    connect(this, SIGNAL(sendProcessedDataToSaveIntoDB(QString)),
            mActivityReminderDBConnector, SLOT(sendDataToSaveIntoDB(QString)));
    connect(mActivityReminderDBConnector, SIGNAL(processDBAckToUI(QString)),
            mActivityReminderUIConnector, SLOT(writeData(QString)));

    utility::GenericLogger::getLogger()->logInfo("ActivityReminderCoreMain::init, DB conStatus:" + QString::number(conStatus).toStdString());

    return conStatus;
}

void ActivityReminderCoreMain::processRecivedDataToSaveIntoDB(QString message)
{
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderCoreMain::processRecivedDataToSaveIntoDB, DB conStatus:"
                                                 + message.toStdString());

    //TODO - Lets process data, once data is process send to save into the database

    emit sendProcessedDataToSaveIntoDB(message);
}
