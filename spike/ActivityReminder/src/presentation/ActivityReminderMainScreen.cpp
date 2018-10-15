#include "ui_ActivityReminderMainScreen.h"

#include "ActivityReminderMainScreen.h"

//Const & Utility
#include "ActivityReminderConst.h"
#include "GenericLogger.h"

ActivityReminderMainScreen::ActivityReminderMainScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActivityReminderMainScreen)
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderMainScreen::ActivityReminderMainScreen");
    ui->setupUi(this);
}

ActivityReminderMainScreen::~ActivityReminderMainScreen()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderMainScreen::~ActivityReminderMainScreen");
}

int ActivityReminderMainScreen::init()
{
    int retStaus = gActivityReminderConst::UNKNOWN_ERROR;

    connect(ui->pushButtonAdd, SIGNAL(pressed()), this, SLOT(writeData()));

    retStaus = gActivityReminderConst::SUCCESS;

    return retStaus;
}

void ActivityReminderMainScreen::setCurrentAction(QString info)
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderMainScreen::setCurrentAction");
    ui->labelStatus->setText(info);
}

void ActivityReminderMainScreen::end()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderMainScreen::end");

    delete ui;
}

void ActivityReminderMainScreen::readData()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderMainScreen::readData");
}

void ActivityReminderMainScreen::writeData()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderMainScreen::writeData");
    emit requestToAddUiData("Connected");
}
