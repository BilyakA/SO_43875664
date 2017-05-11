#include <QCoreApplication>
#include "DataSender.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DataSender* sender = new DataSender();
    sender->start();

    return a.exec();
}
