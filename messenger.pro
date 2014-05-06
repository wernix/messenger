#-------------------------------------------------
#
# Project created by QtCreator 2014-04-26T09:33:12
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = messenger
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aboutdialog.cpp \
    preferencesdialog.cpp \
    message.cpp \
    chatboxdialog.cpp \
    chatboxdialogcontent.cpp \
    contactslistmodel.cpp \
    myprofile.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    preferencesdialog.h \
    message.h \
    chatboxdialog.h \
    chatboxdialogcontent.h \
    myprofile.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    preferencesdialog.ui \
    chatboxform.ui \
    chatboxdialog.ui \
    chatboxdialogcontent.ui
