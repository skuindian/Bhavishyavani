#include <QCoreApplication>

#include "ActivityReminderProcessLauncher.h"

#include "ActivityReminderConst.h"
#include "GenericLogger.h"

#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    //Set logger file name
    utility::GenericLogger::getLogger()->setupLogger("ActivityReminder.log");
    utility::GenericLogger::getLogger()->logInfo("main, Starting Application");

    ActivityReminderProcessLauncher activityReminderProcessLauncher;

    if(activityReminderProcessLauncher.init() ==  gActivityReminderConst::SUCCESS)
    {
        std::cout << "Please do not close the window...." << std::endl;
        utility::GenericLogger::getLogger()->logInfo("init() Success, launching");
    }
    else
    {
        utility::GenericLogger::getLogger()->logError("Unable to launch application, exiting");
    }

    return app.exec();
}
