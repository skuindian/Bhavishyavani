QT += core
QT -= gui

CONFIG += c++11

TARGET = ActivityReminder
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += src\main\main.cpp \
    src/main/ActivityReminderProcessLauncher.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
            include \
            src/utility/

HEADERS += \
    src/main/ActivityReminderProcessLauncher.h

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += $${OUT_PWD}/../../bin/GenericUtils.dll

win32 {
    TARGET_CUSTOM_EXT = .exe
}

CONFIG( debug, debug|release ) {
    #debug
    #DEPENDENT_PATH = $${OUT_PWD}/debug/
    #DEPENDENT_TARGET = $${OUT_PWD}/debug/$${TARGET}$${TARGET_CUSTOM_EXT}
    #DEPLOY_PATH = $${OUT_PWD}/debug/../../../bin/
} else {
    #release
    DEPENDENT_PATH = $${OUT_PWD}/release/
    DEPENDENT_TARGET = $${OUT_PWD}/release/$${TARGET}$${TARGET_CUSTOM_EXT}
    DEPLOY_PATH = $${OUT_PWD}/release/../../../bin/

    warning($${QMAKE_COPY} $${DEPENDENT_TARGET} $${DEPLOY_PATH})
    QMAKE_POST_LINK = $${QMAKE_COPY} $${DEPENDENT_TARGET} $${DEPLOY_PATH}
}
