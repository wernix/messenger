#-------------------------------------------------
#
# Project created by QtCreator 2014-04-26T09:33:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = messenger
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    preferencesdialog.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    preferencesdialog.h \
    aboutdialog.h

FORMS    += mainwindow.ui \
    preferencesdialog.ui \
    aboutdialog.ui \
    preferencesdialog.ui
