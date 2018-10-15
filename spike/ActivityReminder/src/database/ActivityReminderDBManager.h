#ifndef ACTIVITYREMINDERDBMANAGER_H
#define ACTIVITYREMINDERDBMANAGER_H

#include <QObject>

class ActivityReminderDBConnector;

class ActivityReminderDBManager : public QObject
{
    Q_OBJECT
public:
    explicit ActivityReminderDBManager(QObject *parent = nullptr);

    int init();

private:
    ActivityReminderDBConnector *mActivityReminderDBConnector;

signals:

public slots:
};

#endif // ACTIVITYREMINDERDBMANAGER_H
