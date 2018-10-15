#include "ActivityReminderSplashScreen.h"
#include "ui_ActivityReminderSplashScreen.h"

//Utility
#include "GenericLogger.h"

ActivityReminderSplashScreen::ActivityReminderSplashScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActivityReminderSplashScreen)
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderSplashScreen::ActivityReminderSplashScreen");
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

ActivityReminderSplashScreen::~ActivityReminderSplashScreen()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderSplashScreen::~ActivityReminderSplashScreen");
    delete ui;
}

void ActivityReminderSplashScreen::setProgressStatus(int progress)
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderSplashScreen::setProgressStatus, progress:" + QString::number(progress).toStdString());
    ui->progressBar->setValue(progress);
}

void ActivityReminderSplashScreen::setProgressText(QString text)
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderSplashScreen::setProgressStatus, text" + text.toStdString());
    ui->labelStatusText->setText(text);
}
