#-------------------------------------------------
#
# Project created by QtCreator 2018-10-03T07:59:50
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ActivityReminderUi
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


SOURCES += \
        src/presentation/main.cpp \
        src/presentation/ActivityReminderMainScreen.cpp \
    src/presentation/ActivityReminderSplashScreen.cpp \
    src/presentation/ActivityReminderCoreConnector.cpp \
    src/presentation/ActivityReminderMainManager.cpp

HEADERS += \
        src/presentation/ActivityReminderMainScreen.h \
    src/presentation/ActivityReminderSplashScreen.h \
    src/presentation/ActivityReminderCoreConnector.h \
    src/presentation/ActivityReminderMainManager.h

FORMS += \
        src/presentation/ActivityReminderMainScreen.ui \
    src/presentation/ActivityReminderSplashScreen.ui

INCLUDEPATH += \
            include \
            src/utility \
            src/helper

RESOURCES += \
    images/images.qrc

LIBS += $${OUT_PWD}/../../bin/GenericUtils.dll
LIBS += $${OUT_PWD}/../../bin/ActivityReminderHelper.dll

win32 {
    TARGET_CUSTOM_EXT = .exe
    DEPLOY_COMMAND = windeployqt$$TARGET_CUSTOM_EXT
    #DEPLOY_COMMAND = $$[QT_INSTALL_BINS]/windeployqt$$TARGET_CUSTOM_EXT
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

    #Use += instead of = if you use multiple QMAKE_POST_LINKs
    warning($${DEPLOY_COMMAND} $${DEPENDENT_TARGET} --dir $${DEPLOY_PATH})
    QMAKE_POST_LINK = $${DEPLOY_COMMAND} $${DEPENDENT_TARGET} --dir $${DEPLOY_PATH}$$escape_expand(\n\t)

    warning($${QMAKE_COPY} $${DEPENDENT_TARGET} $${DEPLOY_PATH})
    QMAKE_POST_LINK += $${QMAKE_COPY} $${DEPENDENT_TARGET} $${DEPLOY_PATH}

    #--------------------------------------------------------------------------
    #Bellow will only work if does make install
    #--------------------------------------------------------------------------
    #Copy the executable
    #target.path = $${DEPLOY_PATH}
    #target.files = $${DEPENDENT_TARGET}
    #target.extra  = custom commands to run, eg. `touch somefile.txt`
    #warning($${DEPENDENT_TARGET} $${DEPLOY_PATH})

    #INSTALLS += \
    #   target
}
