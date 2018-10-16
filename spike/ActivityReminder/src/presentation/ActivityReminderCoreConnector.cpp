#include "ActivityReminderCoreConnector.h"

//Common classes & utility
#include "ActivityReminderConst.h"
#include "GenericLogger.h"

//QT Interface
#include <QNetworkInterface>
#include <QDataStream>
#include <QDebug>

//Helper class
#include "ActivityReminderConfigReader.h"

ActivityReminderCoreConnector::ActivityReminderCoreConnector(QObject *parent):
    QObject(parent),
    mTcpSocket(nullptr)
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderCoreConnector::ActivityReminderCoreConnector");
}

int ActivityReminderCoreConnector::init()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderCoreConnector::init");

    mTcpSocket = new QTcpSocket(this);

    connect(mTcpSocket, SIGNAL(connected()), this, SLOT(connectedToServerSuccess()));
    connect(mTcpSocket, SIGNAL(disconnected()), this, SLOT(disconnectFromServer()));
    connect(mTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(connectedToServerError(QAbstractSocket::SocketError)));

    connect(mTcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));

    //To update the status of the server connection
    emit requestMessage("Connecting to server");
    connectToServer(helper::ActivityReminderConfigReader::getInstence()->getServerIP().c_str(),
                    helper::ActivityReminderConfigReader::getInstence()->getServerUIPort());

    if(!mTcpSocket->waitForConnected())
    {

        utility::GenericLogger::getLogger()->logInfo("ActivityReminderCoreConnector::init, Error while connection");
        return gActivityReminderConst::SERVER_NOT_CONNECTED;
    }

    return gActivityReminderConst::SUCCESS;
}

void ActivityReminderCoreConnector::end()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderCoreConnector::end");
    mTcpSocket->close();
}

void ActivityReminderCoreConnector::connectToServer(QString serverAddress, int port)
{
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderCoreConnector::connectToServer, ,server address:" +
                                                 serverAddress.toStdString() + ", port:" +
                                                 QString::number(port).toStdString());

    mTcpSocket->connectToHost(serverAddress, port);

}

void ActivityReminderCoreConnector::connectedToServerSuccess()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderCoreConnector::"
                                                  "connectedToServerSuccess");
    emit requestMessage("Connected to server");
}

void ActivityReminderCoreConnector::disconnectFromServer()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderCoreConnector::"
                                                  "disconnectFromServer");
    mTcpSocket->close();
    emit requestMessage("Connection closed from server");
}

void ActivityReminderCoreConnector::connectedToServerError(QAbstractSocket::SocketError error)
{
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderCoreConnector::connectedToServerError"
                                                 ", error code:" + QString::number(error).toStdString());

    emit requestMessage("Error while connecting to server");
}

void ActivityReminderCoreConnector::readData()
{
    emit requestMessage("Received data for request");

    QDataStream in(mTcpSocket);
    in.setVersion(QDataStream::Qt_4_2);

    QString message;
    in >> message;

    utility::GenericLogger::getLogger()->logInfo("ActivityReminderCoreConnector::readData, data:" + message.toStdString());
}

void ActivityReminderCoreConnector::writeData(QString message)
{
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderCoreConnector::writeData, data:" + message.toStdString() );

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << message;

    mTcpSocket->write(block);
    emit requestMessage("Sending request data to server");
}
