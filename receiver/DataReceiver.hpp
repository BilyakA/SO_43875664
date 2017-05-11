#ifndef DATARECEIVER_HPP
#define DATARECEIVER_HPP

#include <QObject>
#include <QLocalSocket>
#include <QDataStream>
#include "../dataStruct.h"

class DataReceiver : public QObject
{
    Q_OBJECT
public:
    explicit DataReceiver(QObject *parent = 0);

signals:

public slots:
    void start();
private slots:
    void requestNewFrame();
    void readSocket();
    void handleSocketError(QLocalSocket::LocalSocketError socketError);
private:
    QLocalSocket* dataSocket;
    QDataStream dataStream;
    dataStruct frame;
};

#endif // DATARECEIVER_HPP
