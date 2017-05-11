QT =

QT += core network

CONFIG += c++11

TARGET = Sender
CONFIG += console

TEMPLATE = app

SOURCES += main.cpp \
    DataReceiver.cpp

HEADERS += \
    DataReceiver.hpp
