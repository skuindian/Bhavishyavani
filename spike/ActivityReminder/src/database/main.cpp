#include <QCoreApplication>

#include "ActivityReminderDBManager.h"

#include "ActivityReminderConst.h"
#include "GenericLogger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    utility::GenericLogger::getLogger()->setupLogger("ActivityReminderDB.log");
    utility::GenericLogger::getLogger()->logInfo("main, Starting Application");

    ActivityReminderDBManager activityReminderDBManager;
    if(activityReminderDBManager.init() == gActivityReminderConst::SUCCESS)
    {
        utility::GenericLogger::getLogger()->logInfo("main, DB Application Started");
    }
    else
    {
        utility::GenericLogger::getLogger()->logError("main, Error while starting DB application");
        exit(0);
    }

    return a.exec();
}
