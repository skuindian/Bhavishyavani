#ifndef ACTIVITYREMINDERDBCONNECTOR_H
#define ACTIVITYREMINDERDBCONNECTOR_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>

class ActivityReminderDBConnector: public QObject
{
    Q_OBJECT

private:
    QTcpSocket *mTcpSocket;

    QString getMessageIdentifier();
    void connectToServer(QString serverAddress, int port);

    void saveDataIntoDB(QString message);

public:
    explicit ActivityReminderDBConnector(QObject *parent = nullptr);
    int init();
    void end();

private slots:
    void connectedToServerSuccess();
    void connectedToServerError(QAbstractSocket::SocketError error);
    void disconnectFromServer();
    void readData();

public slots:
    void writeData(QString message);
};

#endif // ACTIVITYREMINDERDBCONNECTOR_H
