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
    GlobalManage.cpp \
    add_iport.cpp \
    add_iport_pro.cpp \
    add_reactor_page.cpp \
    choose_iport_next.cpp \
    choose_oport_pre.cpp \
    choose_preornext.cpp \
    choose_reactor_tochange.cpp \
    delete_choose.cpp \
    fun.cpp \
    main.cpp \
    net_show.cpp \
    next_choose.cpp \
    pre_choose.cpp \
    product_info.cpp

HEADERS += \
    Class_defi.h \
    GlobalManage.h \
    Painter.h \
    add_iport.h \
    add_iport_pro.h \
    add_reactor_page.h \
    choose_iport_next.h \
    choose_oport_pre.h \
    choose_preornext.h \
    choose_reactor_tochange.h \
    delete_choose.h \
    extend.h \
    net_show.h \
    next_choose.h \
    pre_choose.h \
    product_info.h

FORMS += \
    add_iport.ui \
    add_iport_pro.ui \
    add_reactor_page.ui \
    choose_iport_next.ui \
    choose_oport_pre.ui \
    choose_preornext.ui \
    choose_reactor_tochange.ui \
    delete_choose.ui \
    net_show.ui \
    next_choose.ui \
    pre_choose.ui \
    product_info.ui \
    reactor.ui

TRANSLATIONS += \
    Reactor_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
