#include "ActivityReminderDBConnector.h"

//Common classes & utility
#include "ActivityReminderConst.h"
#include "GenericLogger.h"

//QT Interface
#include <QDataStream>

//Helper class
#include "ActivityReminderConfigReader.h"

ActivityReminderDBConnector::ActivityReminderDBConnector(QObject *parent):
    QObject(parent),
    mTcpSocket(nullptr)
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderDBConnector::ActivityReminderDBConnector");
}

int ActivityReminderDBConnector::init()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderDBConnector::init");

    mTcpSocket = new QTcpSocket(this);

    connect(mTcpSocket, SIGNAL(connected()), this, SLOT(connectedToServerSuccess()));
    connect(mTcpSocket, SIGNAL(disconnected()), this, SLOT(disconnectFromServer()));
    connect(mTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(connectedToServerError(QAbstractSocket::SocketError)));

    connect(mTcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));

    //To update the status of the server connection
    connectToServer(helper::ActivityReminderConfigReader::getInstence()->getServerIP().c_str(),
                    helper::ActivityReminderConfigReader::getInstence()->getServerDBPort());

    if(!mTcpSocket->waitForConnected())
    {

        utility::GenericLogger::getLogger()->logInfo("ActivityReminderDBConnector::init, Error while connection");
        return gActivityReminderConst::SERVER_NOT_CONNECTED;
    }

    return gActivityReminderConst::SUCCESS;
}

void ActivityReminderDBConnector::end()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderDBConnector::end");
    mTcpSocket->close();
}

void ActivityReminderDBConnector::connectToServer(QString serverAddress, int port)
{
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderDBConnector::connectToServer, ,server address:" +
                                                 serverAddress.toStdString() + ", port:" +
                                                 QString::number(port).toStdString());

    mTcpSocket->connectToHost(serverAddress, port);

}

void ActivityReminderDBConnector::connectedToServerSuccess()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderDBConnector::"
                                                  "connectedToServerSuccess");
}

void ActivityReminderDBConnector::disconnectFromServer()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderDBConnector::"
                                                  "disconnectFromServer");
    mTcpSocket->close();
}

void ActivityReminderDBConnector::connectedToServerError(QAbstractSocket::SocketError error)
{
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderDBConnector::connectedToServerError"
                                                 ", error code:" + QString::number(error).toStdString());
}

void ActivityReminderDBConnector::readData()
{
    QDataStream in(mTcpSocket);
    in.setVersion(QDataStream::Qt_4_2);

    QString message;
    in >> message;

    utility::GenericLogger::getLogger()->logInfo("ActivityReminderDBConnector::readData, data:" + message.toStdString());

    //Adding data into the database
    saveDataIntoDB(message);
}

void ActivityReminderDBConnector::saveDataIntoDB(QString message)
{
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderDBConnector::saveDataIntoDB, data:"
                                                 + message.toStdString());

    //TODO - Add data into DB & based on this send the status

    writeData(message + "-SUCCESS");
}

void ActivityReminderDBConnector::writeData(QString message)
{
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderDBConnector::writeData, data:" + message.toStdString() );

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << message;

    mTcpSocket->write(block);
}
