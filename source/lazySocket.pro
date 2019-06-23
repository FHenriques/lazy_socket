QT += quick network xml
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    userdata.cpp \
    ConstVars/xml-config-reader.cpp \
    Communication/socket-tool-server.cpp \
    Communication/socket-tool-client.cpp \
    Communication/clients-monitor.cpp \
    Communication/socket-client-datapacket.cpp \
    Models/socket-clients-list.cpp \
    Models/socket-clients-model.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    userdata.h \
    ConstVars/xml-config-reader.h \
    Communication/socket-tool-server.h \
    Communication/socket-tool-client.h \
    Communication/clients-monitor.h \
    Communication/socket-client-datapacket.h \
    Models/socket-clients-list.h \
    Models/socket-clients-model.h

DISTFILES += \
    ../build-untitled-Desktop_Qt_5_11_2_MinGW_32bit-Debug/debug/lazy_ini.xml \
    ../build-untitled-Desktop_Qt_5_11_2_MinGW_32bit-Debug/debug/readme.md
