#ifndef ACTIVITYREMINDERCOREMAIN_H
#define ACTIVITYREMINDERCOREMAIN_H

#include <QObject>

class ActivityReminderUIConnector;
class ActivityReminderDBConnector;

class ActivityReminderCoreMain : public QObject
{
    Q_OBJECT
public:
    explicit ActivityReminderCoreMain(QObject *parent = nullptr);
    ~ActivityReminderCoreMain();

    int init();

private:
    ActivityReminderUIConnector *mActivityReminderUIConnector;
    ActivityReminderDBConnector *mActivityReminderDBConnector;

signals:
    void sendProcessedDataToSaveIntoDB(QString message);

private slots:
    void processRecivedDataToSaveIntoDB(QString message);
};

#endif // ACTIVITYREMINDERCOREMAIN_H
