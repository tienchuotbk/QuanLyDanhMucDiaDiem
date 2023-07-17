QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    changeinfor.cpp \
    client.cpp \
    comment.cpp \
    friendinfo.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    postscreen.cpp \
    singleton.cpp \
    user.cpp

HEADERS += \
    changeinfor.h \
    client.h \
    comment.h \
    friendinfo.h \
    login.h \
    mainwindow.h \
    post.h \
    postscreen.h \
    singleton.h \
    user.h

FORMS += \
    changeinfor.ui \
    comment.ui \
    friendinfo.ui \
    login.ui \
    mainwindow.ui \
    postscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
