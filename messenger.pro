#-------------------------------------------------
#
# Project created by QtCreator 2014-04-26T09:33:12
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = messenger
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aboutdialog.cpp \
    preferencesdialog.cpp \
    chatboxform.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    preferencesdialog.h \
    chatboxform.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    preferencesdialog.ui \
    chatboxform.ui
