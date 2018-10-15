#include <QDataStream>

#include "ActivityReminderDBConnector.h"

#include "ActivityReminderConst.h"

#include "GenericLogger.h"

ActivityReminderDBConnector::ActivityReminderDBConnector(QObject *parent):
    QObject(parent),
    mServer(nullptr),
    mDBSocket(nullptr)
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderDBConnector::ActivityReminderDBConnector");

}

int ActivityReminderDBConnector::init()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderDBConnector::init");
    mServer = new QTcpServer(this);
    connect(mServer, SIGNAL(newConnection()), this, SLOT(clientConnected()));

    int conStatus = listenIncomingRequest();

    return conStatus;
}

void ActivityReminderDBConnector::end()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderDBConnector::end");
    if(mServer)
    {
        mServer->close();
    }
}

int ActivityReminderDBConnector::listenIncomingRequest()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderDBConnector::listenIncomingRequest");

    if(!mServer->listen(QHostAddress::LocalHost, 8001))
    {
        return gActivityReminderConst::SERVER_NOT_STARTED;
    }

    return gActivityReminderConst::SUCCESS;
}

void ActivityReminderDBConnector::clientConnected()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderDBConnector::clientConnected");
    mDBSocket = mServer->nextPendingConnection();
    connect(mDBSocket, SIGNAL(readyRead()), this, SLOT(readData()));

    //Will not accept any new connection
    mServer->pauseAccepting();
}

void ActivityReminderDBConnector::readData()
{
    QDataStream in(mDBSocket);
    in.setVersion(QDataStream::Qt_4_2);

    QString message;
    in >> message;

    utility::GenericLogger::getLogger()->logInfo("ActivityReminderDBConnector::readData, data:" + message.toStdString());

    emit processDBAckToUI(message);
}

void ActivityReminderDBConnector::sendDataToSaveIntoDB(QString message)
{
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderDBConnector::sendDataToSaveIntoDB, data:"
                                                 + message.toStdString());

    writeData(message);
}

void ActivityReminderDBConnector::writeData(QString message)
{
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderDBConnector::writeData, data:" + message.toStdString() );

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << message;

    mDBSocket->write(block);
}
