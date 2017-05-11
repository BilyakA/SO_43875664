QT =

QT += core network

CONFIG += c++11

TARGET = Sender
CONFIG += console

TEMPLATE = app

SOURCES += main.cpp \
    DataSender.cpp

HEADERS += \
    DataSender.hpp
