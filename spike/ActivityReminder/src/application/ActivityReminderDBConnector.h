#ifndef ACTIVITYREMINDERDBCONNECTOR_H
#define ACTIVITYREMINDERDBCONNECTOR_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>

class ActivityReminderDBConnector: public QObject
{
    Q_OBJECT

public:
    ActivityReminderDBConnector(QObject *parent = nullptr);

    int init();
    void end();

private:
    QTcpServer *mServer;
    QTcpSocket *mDBSocket;

    int listenIncomingRequest();

private slots:
    void clientConnected();
    void readData();

public slots:
    void writeData(QString message);
    void sendDataToSaveIntoDB(QString message);

signals:
    void processDBAckToUI(QString message);
};

#endif // ACTIVITYREMINDERDBCONNECTOR_H
