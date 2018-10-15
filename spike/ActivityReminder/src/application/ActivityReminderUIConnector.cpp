#include <QDataStream>

#include "ActivityReminderUIConnector.h"

#include "ActivityReminderConst.h"

#include "GenericLogger.h"

ActivityReminderUIConnector::ActivityReminderUIConnector(QObject *parent):
    QObject(parent)
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderUIConnector::ActivityReminderUIConnector");
}

int ActivityReminderUIConnector::init()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderUIConnector::init");
    mServer = new QTcpServer(this);
    connect(mServer, SIGNAL(newConnection()), this, SLOT(clientConnected()));

    int conStatus = listenIncomingRequest();

    return conStatus;
}

void ActivityReminderUIConnector::end()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderUIConnector::end");
    if(mServer)
    {
        mServer->close();
    }
}

int ActivityReminderUIConnector::listenIncomingRequest()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderUIConnector::listenIncomingRequest");

    if(!mServer->listen(QHostAddress::LocalHost, 8000))
    {
        return gActivityReminderConst::SERVER_NOT_STARTED;
    }

    return gActivityReminderConst::SUCCESS;
}

void ActivityReminderUIConnector::clientConnected()
{
    utility::GenericLogger::getLogger()->logDebug("ActivityReminderUIConnector::clientConnected");
    mUISocket = mServer->nextPendingConnection();
    connect(mUISocket, SIGNAL(readyRead()), this, SLOT(readData()));

    //Will not accept any new connection
    mServer->pauseAccepting();
}

void ActivityReminderUIConnector::readData()
{
    QDataStream in(mUISocket);
    in.setVersion(QDataStream::Qt_4_2);

    QString message;
    in >> message;

    utility::GenericLogger::getLogger()->logInfo("ActivityReminderUIConnector::readData, data:" + message.toStdString());
    emit processRecivedDataFromUI(message);
}

void ActivityReminderUIConnector::writeData(QString message)
{
    utility::GenericLogger::getLogger()->logInfo("ActivityReminderUIConnector::writeData, data:" + message.toStdString() );

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << message;

    mUISocket->write(block);
}
