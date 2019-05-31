#-------------------------------------------------
#
# Project created by QtCreator 2019-04-26T09:43:55
#
#-------------------------------------------------


#INCLUDEPATH += /usr/include/gtest
#INCLUDEPATH += /usr/include/gmock
#
#
#LIBS += -lgtest -L<path_to_gtest_lib>
#LIBS += -lgmock -L<path_to_gmock_lib>



QT       += core gui widgets serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = labyrinthgame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#For Windows
CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    mazewidget.cpp \
    points.cpp \
    serialreader.cpp

HEADERS += \
        mainwindow.h \
    mazewidget.h \
    points.h \
    serialreader.h

FORMS += \
        mainwindow.ui
