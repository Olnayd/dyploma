QT += core sql network
QT -= gui

CONFIG += console c++11
CONFIG -= app_bundle

TEMPLATE = app


DISTFILES += \
    README.md

HEADERS += \
    common/controller/CController.h \
    common/controller/CSubController.h \
    common/controller/EControllerProcessingStep.h \
    common/controller/IController.h \
    common/helper/commonhelper.h \
    common/job/IJob.h \
    common/job/JobQueue.hpp \
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
    network/processor/course/CCourseProcessor.hpp \
    network/processor/course/RequestType.hpp \
    network/processor/course/ResponseType.hpp \
    network/CNetworkClient.hpp \
    network/CResponseContext.hpp \
    CRootComponent.h \
    controller/subController/CUserSubCtrl.h \
    network/processor/course/ICourseResponseHandle.hpp

SOURCES += \
    common/controller/CController.cpp \
    common/controller/IController.cpp \
    common/helper/commonhelper.cpp \
    common/job/IJob.cpp \
    common/job/JobQueue.cpp \
    common/observer/ISubject.cpp \
    common/version.cpp \
    controller/subController/CImageStorageSubCtrl.cpp \
    controller/subController/CSqlSubCtrl.cpp \
    controller/subController/CTextStorageSubCtrl.cpp \
    controller/CCourseCtrl.cpp \
    database/connection/CDatabaseConnection.cpp \
    database/connection/CDatabaseConnectionFactory.cpp \
    database/query/SqlGetSchemaVersion.cpp \
    database/query/SqlImageStorageStatement.cpp \
    database/query/sqlquery.cpp \
    database/query/SqlTextStorageStatement.cpp \
    database/CSqlConstants.cpp \
    network/processor/course/CCourseProcessor.cpp \
    network/CNetworkClient.cpp \
    network/CResponseContext.cpp \
    CRootComponent.cpp \
    main.cpp \
    common/controller/CSubController.cpp \
    controller/subController/CUserSubCtrl.cpp
