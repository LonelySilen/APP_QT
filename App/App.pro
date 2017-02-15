#-------------------------------------------------
#
# Project created by Silen 2015-11
#
#-------------------------------------------------

QT       += core xml sql network multimedia svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = App
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tablewidget.cpp \
    plotter.cpp \
    qdelegate.cpp \
    login/login.cpp \
    login/userdata.cpp \
    login/myhelper.cpp \
    login/logining.cpp \
    login/qmenubutton.cpp \
    list/friendslist.cpp \
    chatitem.cpp \
    chatview.cpp \
    filerecive.cpp \
    filetransfer.cpp \
    frienditem.cpp \
    groupitem.cpp \
    msggroupbox.cpp \
    mywidget.cpp

HEADERS  += mainwindow.h \
    tablewidget.h \
    qheader.h \
    plotter.h \
    qdelegate.h \
    login/login.h \
    login/userdata.h \
    login/myhelper.h \
    login/logining.h \
    login/qmenubutton.h \
    list/friendslist.h \
    chatitem.h \
    chatview.h \
    filerecive.h \
    filetransfer.h \
    frienditem.h \
    groupitem.h \
    msggroupbox.h \
    mywidget.h

RESOURCES += \
    res.qrc

RC_ICONS = App.ico
