#ifndef ACTIVITYREMINDERUICONNECTO_H
#define ACTIVITYREMINDERUICONNECTO_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>

class ActivityReminderUIConnector: public QObject
{
    Q_OBJECT

public:
    ActivityReminderUIConnector(QObject *parent = nullptr);

    int init();
    void end();

private:
    QTcpServer *mServer;
    QTcpSocket *mUISocket;

    int listenIncomingRequest();

private slots:
    void clientConnected();
    void readData();

public slots:
    void writeData(QString message);

signals:
    void processRecivedDataFromUI(QString message);
};

#endif // ACTIVITYREMINDERUICONNECTO_H
