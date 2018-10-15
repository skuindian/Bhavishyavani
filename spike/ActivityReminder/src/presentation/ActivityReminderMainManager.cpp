#include "ActivityReminderMainManager.h"

//Const & Utility
#include "ActivityReminderConst.h"
#include "GenericLogger.h"

//UI Screens
#include "ActivityReminderSplashScreen.h"
#include "ActivityReminderMainScreen.h"

//Communication
#include "ActivityReminderCoreConnector.h"

ActivityReminderMainManager::ActivityReminderMainManager(QObject *parent) :
    QObject(parent),
    mActivityReminderCoreConnector(nullptr),
    mActivityReminderSplashScreen(nullptr),
    mActivityReminderMainScreen(nullptr)
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderMainManager::ActivityReminderMainManager");
}

ActivityReminderMainManager::~ActivityReminderMainManager()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderMainManager::~ActivityReminderMainManager");

    //End and cleanup
    end();
}

void ActivityReminderMainManager::showSplashScreen()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderMainManager::showSplashScreen");
    mActivityReminderSplashScreen = new ActivityReminderSplashScreen();
    mActivityReminderSplashScreen->showMaximized();
    mActivityReminderSplashScreen->setProgressStatus(0);
    mActivityReminderSplashScreen->setProgressText("Starting Application...");
}

void ActivityReminderMainManager::hideSplashScreen()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderMainManager::hide");
    mActivityReminderSplashScreen->hide();
}

int ActivityReminderMainManager::init()
{
    int retStaus = gActivityReminderConst::UNKNOWN_ERROR;
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderMainManager::init");

    mActivityReminderSplashScreen->setProgressStatus(10);
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderMainManager::init, starting network connection");
    mActivityReminderSplashScreen->setProgressText("Starting Network Connection...");
    mActivityReminderCoreConnector = new ActivityReminderCoreConnector;
    retStaus = mActivityReminderCoreConnector->init();
    mActivityReminderSplashScreen->setProgressStatus(50);

    if(retStaus == gActivityReminderConst::SUCCESS)
    {
        utility::GenericLogger::getLogger()->logInfo("ActivityReminderMainManager::init, loading UI component");
        mActivityReminderSplashScreen->setProgressText("Loading UI...");
        mActivityReminderSplashScreen->setProgressStatus(90);
        mActivityReminderMainScreen = new ActivityReminderMainScreen;
        retStaus = mActivityReminderMainScreen->init();

        //Denine all signal slot
        connect(mActivityReminderCoreConnector, SIGNAL(requestMessage(QString)),
                mActivityReminderMainScreen, SLOT(setCurrentAction(QString)));
        connect(mActivityReminderMainScreen, SIGNAL(requestToAddUiData(QString)),
                mActivityReminderCoreConnector, SLOT(writeData(QString)));
    }
    else
    {
        utility::GenericLogger::getLogger()->logInfo("ActivityReminderMainManager::init, unable to connect");
        mActivityReminderSplashScreen->setProgressText("Starting Network...ERROR");
        mActivityReminderSplashScreen->setProgressStatus(90);
    }

    return retStaus;
}

void ActivityReminderMainManager::end()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderMainManager::end");
    if(mActivityReminderCoreConnector)
    {
        mActivityReminderCoreConnector->end();
        delete mActivityReminderCoreConnector;
        mActivityReminderCoreConnector = 0;
    }

    if(mActivityReminderMainScreen)
    {
        mActivityReminderMainScreen->end();
        delete mActivityReminderMainScreen;
        mActivityReminderMainScreen = 0;
    }

    if(mActivityReminderSplashScreen)
    {
        delete mActivityReminderSplashScreen;
        mActivityReminderSplashScreen = 0;
    }
}

void ActivityReminderMainManager::launch()
{
    if(mActivityReminderMainScreen)
    {
        mActivityReminderMainScreen->show();
    }
}
