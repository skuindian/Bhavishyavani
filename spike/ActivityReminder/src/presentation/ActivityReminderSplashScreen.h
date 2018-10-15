#ifndef ACTIVITYREMINDERSPLASHSCREEN_H
#define ACTIVITYREMINDERSPLASHSCREEN_H

#include <QWidget>

namespace Ui {
class ActivityReminderSplashScreen;
}

class ActivityReminderSplashScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ActivityReminderSplashScreen(QWidget *parent = 0);
    ~ActivityReminderSplashScreen();

private:
    Ui::ActivityReminderSplashScreen *ui;

public slots:
    void setProgressStatus(int progress);
    void setProgressText(QString text);
};

#endif // ACTIVITYREMINDERSPLASHSCREEN_H
