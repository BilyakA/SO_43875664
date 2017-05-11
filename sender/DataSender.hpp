#ifndef DATASENDER_HPP
#define DATASENDER_HPP

#include <QObject>
#include <QLocalServer>
#include <QList>
#include <QLocalSocket>
#include <QDataStream>
#include <QByteArray>
#include <QTimer>
#include "../dataStruct.h"

class DataSender : public QObject
{
    Q_OBJECT
public:
    explicit DataSender(QObject *parent = 0);

signals:

public slots:
    void start();
private slots:
    void handleNewConnection();
    void writeSocket();
private:
    QLocalServer* dataServer;
    QList<QLocalSocket*> dataSockets;
    QDataStream* dataStrem;
    QByteArray* dataByteArray;
    QTimer* dataSendTimer;
    dataStruct frame;
};

#endif // DATASENDER_HPP
