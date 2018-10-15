#ifndef ACTIVITYREMINDERMAINSCREEN_H
#define ACTIVITYREMINDERMAINSCREEN_H

#include <QWidget>

namespace Ui {
class ActivityReminderMainScreen;
}

class ActivityReminderSplashScreen;
class ActivityReminderProcessLauncher;
class ActivityReminderCoreConnector;

class ActivityReminderMainScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ActivityReminderMainScreen(QWidget *parent = 0);
    ~ActivityReminderMainScreen();

    int init();
    void end();

    void readData();

private:
    Ui::ActivityReminderMainScreen *ui;
    ActivityReminderSplashScreen *mActivityReminderSplashScreen;
    ActivityReminderProcessLauncher *mActivityReminderProcessLauncher;
    ActivityReminderCoreConnector *mActivityReminderCoreConnector;

private slots:
    void writeData();
    void setCurrentAction(QString);

signals:
    void requestToAddUiData(QString message);
};

#endif // ACTIVITYREMINDERMAINSCREEN_H
