QT = core # Для работы с базовым функционалом QT

QT -= gui # Отключает графический интерфейс пользователя

QT += core network # Для работы с сетями
QT += sql # Для работы с базами данных

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        functions_for_server.cpp \
        main.cpp \
        tcp_server.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    functions_for_server.h \
    singleton.h \
    tcp_server.h
