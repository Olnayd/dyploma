QT += core sql
QT -= gui

CONFIG += console c++11
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
    common/controller/CController.h \
    common/controller/CSubController.h \
    common/controller/EControllerProcessingStep.h \
    common/controller/IController.h \
    common/helper/commonhelper.h \
    common/observer/IObserver.h \
    common/observer/ISubject.h \
    common/version.h \
    controller/subController/CImageStorageSubCtrl.h \
    controller/subController/CSqlSubCtrl.h \
    controller/subController/CTextStorageSubCtrl.h \
    controller/CCourseCtrl.h \
    database/connection/CDatabaseConnection.h \
    database/connection/CDatabaseConnectionFactory.h \
    database/connection/EStorage.h \
    database/query/SqlGetSchemaVersion.h \
    database/query/SqlImageStorageStatement.h \
    database/query/SqlQuery.h \
    database/query/SqlTextStorageStatement.h \
    database/CSqlConstants.h \
    CRootComponent.h

SOURCES += \
    common/controller/CController.cpp \
    common/controller/IController.cpp \
    common/helper/commonhelper.cpp \
    common/observer/ISubject.cpp \
    common/version.cpp \
    controller/subController/CImageStorageSubCtrl.cpp \
    controller/subController/CTextStorageSubCtrl.cpp \
    controller/CCourseCtrl.cpp \
    database/connection/CDatabaseConnection.cpp \
    database/connection/CDatabaseConnectionFactory.cpp \
    database/CSqlConstants.cpp \
    CRootComponent.cpp \
    main.cpp \
    common/controller/CSqlSubCtrl.cpp \
    controller/subController/CSqlSubController.cpp \
    database/query/SqlGetSchemaVersion.cpp \
    database/query/SqlImageStorageStatement.cpp \
    database/query/SqlTextStorageStatement.cpp
