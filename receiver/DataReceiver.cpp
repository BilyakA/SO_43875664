#include "DataReceiver.hpp"
#include <QDebug>
DataReceiver::DataReceiver(QObject *parent)
    : QObject(parent)
    , dataSocket(nullptr)
{
    qRegisterMetaType<QLocalSocket::LocalSocketError>("QLocalSocket::LocalSocketError");
}

void DataReceiver::start()
{
    dataStream.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    requestNewFrame();
}

void DataReceiver::requestNewFrame()
{
    if(dataSocket) {
        dataSocket->disconnect();
        dataSocket->deleteLater();
    }

    dataSocket = new QLocalSocket();
    dataStream.setDevice(dataSocket);

    connect(dataSocket, &QLocalSocket::disconnected, this, &DataReceiver::requestNewFrame);
    connect(dataSocket, &QLocalSocket::readyRead, this, &DataReceiver::readSocket);
    connect(dataSocket, static_cast<void (QLocalSocket::*)(QLocalSocket::LocalSocketError socketError)>(&QLocalSocket::error), this, &DataReceiver::handleSocketError);

    dataSocket->connectToServer("FOO_SOCKET", QIODevice::ReadOnly);
}

void DataReceiver::readSocket()
{
    if(dataStream.readRawData((char*)&frame, sizeof(frame))){
        qDebug() << frame.foo << " is " << frame.bar;
    } else {
        qDebug() << "Error while reading from socket";
    }
}

void DataReceiver::handleSocketError(QLocalSocket::LocalSocketError socketError)
{
    qDebug() << "Socket error: " << socketError;
}
