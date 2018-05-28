QT += core sql network
QT -= gui

CONFIG += console c++11
CONFIG -= app_bundle

TEMPLATE = app


DISTFILES += \
    README.md \

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
    controller/subController/text/query/SqlTextStorageStatement.h \
    controller/subController/text/CTextStorageSubCtrl.h \
    controller/subController/user/query/SqlSignIn.hpp \
    controller/subController/user/query/SqlSignUp.hpp \
    controller/subController/user/CUserSubCtrl.h \
    controller/subController/CImageStorageSubCtrl.h \
    controller/subController/CSqlSubCtrl.h \
    controller/CCourseCtrl.h \
    database/connection/CDatabaseConnection.h \
    database/connection/CDatabaseConnectionFactory.h \
    database/connection/EStorage.h \
    database/query/SqlGetSchemaVersion.h \
    database/query/SqlImageStorageStatement.h \
    database/query/SqlQuery.h \
    database/CSqlConstants.h \
    network/processor/course/types/ClientIdentificator.hpp \
    network/processor/course/types/ClientInformation.hpp \
    network/processor/course/types/ClientType.hpp \
    network/processor/course/types/RequestType.hpp \
    network/processor/course/types/ResponseType.hpp \
    network/processor/course/CCourseProcessor.hpp \
    network/processor/course/ICourseResponseHandle.hpp \
    network/CNetworkClient.hpp \
    network/CResponseContext.hpp \
    CRootComponent.h \
    network/processor/course/types/ErrorType.hpp

SOURCES += \
    common/controller/CController.cpp \
    common/controller/CSubController.cpp \
    common/controller/IController.cpp \
    common/helper/commonhelper.cpp \
    common/job/IJob.cpp \
    common/job/JobQueue.cpp \
    common/observer/ISubject.cpp \
    common/version.cpp \
    controller/subController/text/query/SqlTextStorageStatement.cpp \
    controller/subController/text/CTextStorageSubCtrl.cpp \
    controller/subController/user/query/SqlSignIn.cpp \
    controller/subController/user/query/SqlSignUp.cpp \
    controller/subController/user/CUserSubCtrl.cpp \
    controller/subController/CImageStorageSubCtrl.cpp \
    controller/subController/CSqlSubCtrl.cpp \
    controller/CCourseCtrl.cpp \
    database/connection/CDatabaseConnection.cpp \
    database/connection/CDatabaseConnectionFactory.cpp \
    database/query/SqlGetSchemaVersion.cpp \
    database/query/SqlImageStorageStatement.cpp \
    database/query/SqlQuery.cpp \
    database/CSqlConstants.cpp \
    network/processor/course/types/ClientIdentificator.cpp \
    network/processor/course/types/ClientInformation.cpp \
    network/processor/course/types/ClientType.cpp \
    network/processor/course/CCourseProcessor.cpp \
    network/CNetworkClient.cpp \
    network/CResponseContext.cpp \
    CRootComponent.cpp \
    main.cpp \
    network/processor/course/types/ErrorType.cpp

