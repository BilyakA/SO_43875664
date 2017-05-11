#include <QCoreApplication>
#include "DataReceiver.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DataReceiver* receiver = new DataReceiver();
    receiver->start();

    return a.exec();
}
