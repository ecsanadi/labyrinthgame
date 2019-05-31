include(gtest_dependency.pri)

QT += core gui widgets serialport
QT += widgets

TEMPLATE = app
CONFIG += console c++11
#CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    mainwindow.h \
    mazewidget.h \
    points.h \
    serialreader.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mazewidget.cpp \
    points.cpp \
    serialreader.cpp \
    test/main_testall.cpp \
    test/rulertest.cpp

FORMS += \
        mainwindow.ui

DISTFILES += \
    test/test_lab_img_1.jpg \
    test/test_lab_img_2.jpg \
    test/test_lab_img_3.jpg \
    test/test_lab_img_4.jpg \
    test/test_lab_img_5.jpg \
    test/test_lab_img_6.jpg \
    test/test_lab_img_7.jpg
