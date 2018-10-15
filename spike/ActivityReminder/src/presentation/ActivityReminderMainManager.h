#ifndef ACTIVITYREMINDERMAINMANAGER_H
#define ACTIVITYREMINDERMAINMANAGER_H

#include <QObject>

class ActivityReminderMainScreen;
class ActivityReminderSplashScreen;
class ActivityReminderProcessLauncher;
class ActivityReminderCoreConnector;

class ActivityReminderMainManager : public QObject
{
    Q_OBJECT

public:
    explicit ActivityReminderMainManager(QObject *parent = 0);
    ~ActivityReminderMainManager();

    void showSplashScreen();
    void hideSplashScreen();

    int init();
    void launch();
    void end();

private:
    ActivityReminderCoreConnector *mActivityReminderCoreConnector;
    ActivityReminderSplashScreen *mActivityReminderSplashScreen;
    ActivityReminderMainScreen *mActivityReminderMainScreen;

};

#endif // ACTIVITYREMINDERMAINMANAGER_H
