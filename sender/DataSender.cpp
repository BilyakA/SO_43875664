#include "DataSender.hpp"
#include <QDebug>
#include <QTimer>

DataSender::DataSender(QObject *parent)
    : QObject(parent)
{
    frame.foo = 0;
    frame.bar = false;
}

void DataSender::start()
{
    dataServer = new QLocalServer(this);
    if (!dataServer->listen("FOO_SOCKET")) {
        qDebug() << "Can't create data socket: " << dataServer->errorString();
        return;
    }
    connect(dataServer, &QLocalServer::newConnection, this, &DataSender::handleNewConnection);

    dataByteArray = new QByteArray();
    dataStrem = new QDataStream(dataByteArray, QIODevice::WriteOnly);
    dataStrem->setVersion(QDataStream::Qt_DefaultCompiledVersion);

    dataSendTimer = new QTimer(this);
    dataSendTimer->setInterval(10); // 100Hz
    connect(dataSendTimer, &QTimer::timeout, this, &DataSender::writeSocket);
    dataSendTimer->start();
}

void DataSender::handleNewConnection()
{
    QLocalSocket* socket = dataServer->nextPendingConnection();
    connect(socket, &QLocalSocket::disconnected, [socket](){
       socket->disconnect();
       socket->deleteLater();
    });
    dataSockets.append(socket);
}

void DataSender::writeSocket()
{
    if (++frame.foo > 100) frame.foo = 0;
    (frame.foo == 42) ? frame.bar = true : frame.bar = false;

    while(dataSockets.count()) {
        if (dataSockets[0]->write((char*)&frame, sizeof(frame)) < 0) {
            qDebug() << "Can't write to socket!";
        }
        dataSockets[0]->flush();
        dataSockets[0]->disconnectFromServer();
        dataSockets.removeAt(0);
    }
}
