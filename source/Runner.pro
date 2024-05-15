QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    base.cpp \
    block.cpp \
    character.cpp \
    main.cpp \
    widget_aftergame.cpp \
    widget_game.cpp \
    widget_help.cpp \
    widget_main.cpp \
    widget_rank.cpp

HEADERS += \
    base.h \
    block.h \
    character.h \
    scorelist.h \
    widget_aftergame.h \
    widget_game.h \
    widget_help.h \
    widget_main.h \
    widget_rank.h

FORMS += \
    widget_aftergame.ui \
    widget_game.ui \
    widget_help.ui \
    widget_main.ui \
    widget_rank.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES +=
RC_ICONS = icon.ico
