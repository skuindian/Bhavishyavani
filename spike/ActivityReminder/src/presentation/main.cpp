#include <QApplication>

#include "ActivityReminderMainManager.h"

#include "ActivityReminderConst.h"
#include "GenericLogger.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Set logger file name
    utility::GenericLogger::getLogger()->setupLogger("ActivityReminderUI.log");

    ActivityReminderMainManager activityReminderMainManager;

    utility::GenericLogger::getLogger()->logInfo("Showing splash screen");
    activityReminderMainManager.showSplashScreen();
    app.processEvents();

    if(activityReminderMainManager.init() ==  gActivityReminderConst::SUCCESS)
    {
        utility::GenericLogger::getLogger()->logInfo("init() Success, launching");
        utility::GenericLogger::getLogger()->logInfo("Hiding splash screen");
        activityReminderMainManager.hideSplashScreen();
        utility::GenericLogger::getLogger()->logInfo("Showing main screen");
        activityReminderMainManager.launch();
    }
    else
    {
        utility::GenericLogger::getLogger()->logError("Unable to launch application, exiting");
    }

    return app.exec();
}
