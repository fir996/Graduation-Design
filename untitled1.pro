QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    form.cpp \
    main.cpp \
    u2.cpp \
    ui2.cpp \
    widget.cpp \
    form01.cpp \
    form02.cpp \
    form03.cpp \
    form04.cpp

HEADERS += \
    form.h \
    u2.h \
    ui2.h \
    widget.h \
    form01.h \
    form02.h \
    form03.h \
    form04.h

FORMS += \
    form.ui \
    widget.ui \
    form01.ui \
    form02.ui \
    form03.ui \
    form04.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
