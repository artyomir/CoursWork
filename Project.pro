#-------------------------------------------------
#
# Project created by QtCreator 2017-05-14T12:53:20
#
#-------------------------------------------------

QT       += core gui svg xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    authorization.cpp \
    graphics_view_zoom.cpp \
    mainwindow.cpp \
    registration.cpp \
    roomlabel.cpp \
    svgreader.cpp

HEADERS  += \
    authorization.h \
    graphics_view_zoom.h \
    mainwindow.h \
    registration.h \
    roomlabel.h \
    svgreader.h

FORMS    += \
    authorization.ui \
    mainwindow.ui \
    registration.ui

RESOURCES += \
    sources.qrc
