#include <QCoreApplication>
#include <QDebug>

#include "ActivityReminderCoreMain.h"
#include "ActivityReminderConst.h"

#include "GenericLogger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Set logger file name
    utility::GenericLogger::getLogger()->setupLogger("ActivityReminderCore.log");
    utility::GenericLogger::getLogger()->logInfo("main, Starting Application");

    ActivityReminderCoreMain activityReminderCoreMain;
    if(activityReminderCoreMain.init() == gActivityReminderConst::SUCCESS)
    {
        utility::GenericLogger::getLogger()->logInfo("main, Application Started");
    }
    else
    {
        utility::GenericLogger::getLogger()->logError("main, Error while starting application");
        exit(0);
    }


    return a.exec();
}
