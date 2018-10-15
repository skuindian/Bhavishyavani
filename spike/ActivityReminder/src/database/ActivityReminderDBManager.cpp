#include "ActivityReminderDBManager.h"

//Include dependent class
#include "ActivityReminderDBConnector.h"

//Common classes & utility
#include "ActivityReminderConst.h"
#include "GenericLogger.h"

ActivityReminderDBManager::ActivityReminderDBManager(QObject *parent) : QObject(parent)
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderDBManager::ActivityReminderDBManager");
}

int ActivityReminderDBManager::init()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderDBManager::init");
    int retStatus = gActivityReminderConst::UNKNOWN_ERROR;

    mActivityReminderDBConnector = new ActivityReminderDBConnector(this);
    if(mActivityReminderDBConnector)
    {
        retStatus = mActivityReminderDBConnector->init();
    }

    utility::GenericLogger::getLogger()->logDebug("ActivityReminderDBManager::init, connection status"
                                                  + QString::number(retStatus).toStdString());

    return retStatus;
}

