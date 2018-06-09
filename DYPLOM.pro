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
    controller/subController/text/query/SqlCheckIsUserCreator.hpp \
    controller/subController/text/query/SqlCheckIsUserListener.hpp \
    controller/subController/text/query/SqlCoupleLectureToCourse.hpp \
    controller/subController/text/query/SqlCreateCourse.hpp \
    controller/subController/text/query/SqlCreateTest.hpp \
    controller/subController/text/query/SqlGetAllCourses.hpp \
    controller/subController/text/query/SqlGetCourseListWhereUserIsCreator.hpp \
    controller/subController/text/query/SqlGetCourseListWhereUserIsListener.hpp \
    controller/subController/text/query/SqlGetTopicList.hpp \
    controller/subController/text/query/SqlGetTopicListForCourse.hpp \
    controller/subController/text/query/SqlSubscribeOnCourse.h \
    controller/subController/text/query/SqlTextStorageStatement.hpp \
    controller/subController/text/CTextStorageSubCtrl.h \
    controller/subController/user/query/SqlSignIn.hpp \
    controller/subController/user/query/SqlSignUp.hpp \
    controller/subController/user/CUserSubCtrl.h \
    controller/subController/CImageStorageSubCtrl.h \
    controller/subController/CSqlSubCtrl.h \
    controller/CCourseCtrl.hpp \
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
    network/processor/course/types/Course.hpp \
    network/processor/course/types/CourseListFilter.hpp \
    network/processor/course/types/CourseListFilterType.hpp \
    network/processor/course/types/CourseListWorkingType.hpp \
    network/processor/course/types/CourseTopic.hpp \
    network/processor/course/types/ErrorType.hpp \
    network/processor/course/types/Lecture.hpp \
    network/processor/course/types/RequestType.hpp \
    network/processor/course/types/ResponseType.hpp \
    network/processor/course/types/Test.hpp \
    network/processor/course/CCourseProcessor.hpp \
    network/processor/course/ICourseResponseHandle.hpp \
    network/CNetworkClient.hpp \
    network/CResponseContext.hpp \
    CRootComponent.h \
    controller/subController/text/query/SqlCreateLecture.hpp \
    controller/subController/text/query/SqlGetLecture.hpp \
    controller/subController/text/query/SqlGetLecturePreviewList.hpp \
    controller/subController/text/query/SqlCheckIsLectureIsDone.hpp

SOURCES += \
    common/controller/CController.cpp \
    common/controller/CSubController.cpp \
    common/controller/IController.cpp \
    common/helper/commonhelper.cpp \
    common/job/IJob.cpp \
    common/job/JobQueue.cpp \
    common/observer/ISubject.cpp \
    common/version.cpp \
    controller/subController/text/query/SqlCheckIsUserCreator.cpp \
    controller/subController/text/query/SqlCheckIsUserListener.cpp \
    controller/subController/text/query/SqlCoupleLectureToCourse.cpp \
    controller/subController/text/query/SqlCreateCourse.cpp \
    controller/subController/text/query/SqlCreateTest.cpp \
    controller/subController/text/query/SqlGetAllCourses.cpp \
    controller/subController/text/query/SqlGetCourseListWhereUserIsCreator.cpp \
    controller/subController/text/query/SqlGetCourseListWhereUserIsListener.cpp \
    controller/subController/text/query/SqlGetTopicList.cpp \
    controller/subController/text/query/SqlGetTopicListForCourse.cpp \
    controller/subController/text/query/SqlSubscribeOnCourse.cpp \
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
    network/processor/course/types/Course.cpp \
    network/processor/course/types/CourseListFilter.cpp \
    network/processor/course/types/CourseListFilterType.cpp \
    network/processor/course/types/CourseListWorkingType.cpp \
    network/processor/course/types/CourseTopic.cpp \
    network/processor/course/types/ErrorType.cpp \
    network/processor/course/types/Lecture.cpp \
    network/processor/course/types/Test.cpp \
    network/processor/course/CCourseProcessor.cpp \
    network/CNetworkClient.cpp \
    network/CResponseContext.cpp \
    CRootComponent.cpp \
    main.cpp \
    controller/subController/text/query/SqlCreateLecture.cpp \
    controller/subController/text/query/SqlGetLecture.cpp \
    controller/subController/text/query/SqlGetLecturePreviewList.cpp \
    controller/subController/text/query/SqlCheckIsLectureIsDone.cpp
