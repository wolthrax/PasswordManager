#-------------------------------------------------
#
# Project created by QtCreator 2017-05-29T17:21:52
#
#-------------------------------------------------

QT       += core xml gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PasswordManager
TEMPLATE = app


SOURCES += main.cpp\
    controllers/Controller.cpp \
    entities/Group.cpp \
    entities/CurrentObjects.cpp \
    managers/GroupManager.cpp \
    utils/Generation.cpp \
    entities/Entry.cpp \
    dialogs/AddEntryDialog.cpp \
    managers/EntryManager.cpp \
    managers/converters/EntryConverter.cpp \
    managers/XMLManager.cpp \
    managers/converters/GroupConverter.cpp \
    dialogs/AddGroupDialog.cpp \
    utils/StringConverter.cpp \
    managers/system/UserSystem.cpp \
    managers/system/GroupSystem.cpp \
    dialogs/AddUserDialog.cpp \
    utils/Messages.cpp \
    utils/CheckPassword.cpp \
    dialogs/AddPassword.cpp

HEADERS  += controllers/Controller.h \
    entities/Group.h \
    entities/CurrentObjects.h \
    managers/GroupManager.h \
    utils/Generation.h \
    entities/Entry.h \
    dialogs/AddEntryDialog.h \
    managers/EntryManager.h \
    managers/converters/EntryConverter.h \
    managers/XMLManager.h \
    managers/converters/GroupConverter.h \
    dialogs/AddGroupDialog.h \
    utils/StringConverter.h \
    managers/system/UserSystem.h \
    managers/system/GroupSystem.h \
    dialogs/AddUserDialog.h \
    utils/Messages.h \
    utils/CheckPassword.h \
    dialogs/AddPassword.h

FORMS    += ui/Mainwindow.ui

DISTFILES += \
    libs/NetAPI32.lib

RESOURCES += \
    resources/iconpaths.qrc

win32: LIBS += -lNetAPI32
