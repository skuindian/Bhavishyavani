#ifndef ACTIVITYREMINDERCORECONNECTOR_H
#define ACTIVITYREMINDERCORECONNECTOR_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>

class ActivityReminderCoreConnector: public QObject
{
    Q_OBJECT

private:
    QTcpSocket *mTcpSocket;

    QString getMessageIdentifier();
    void connectToServer(QString serverAddress, int port);

public:
    explicit ActivityReminderCoreConnector(QObject *parent = nullptr);
    int init();
    void end();

private slots:
    void connectedToServerSuccess();
    void connectedToServerError(QAbstractSocket::SocketError error);
    void disconnectFromServer();
    void readData();

public slots:
    void writeData(QString message);

signals:
    void requestMessage(QString reqMessage);
};

#endif // ACTIVITYREMINDERCORECONNECTOR_H
