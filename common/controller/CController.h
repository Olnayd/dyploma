#ifndef CCONTROLLER_H
#define CCONTROLLER_H

#include "EControllerProcessingStep.h"

#include "common/observer/IObserver.h"
#include "common/controller/IController.h"
#include "common/controller/CSubController.h"


namespace common
{
    namespace controller
    {
        class CController
                : public common::controller::IController
                , public common::observer::IObserver

        {
        public:
            CController();
            virtual void initFinished(bool result) override final;
            virtual void prepareShutdownFinished(bool result) override final;

        public:
            virtual void startInitialization() override final;
            virtual void startController() override final;
            virtual void startPrepareShutdown()  override final;

            bool areSubCtrlFinishedPrepareShutdown();
            bool areSubCtrlFinishedInitialization();

        public:

            bool mbIsControllerInitFinished;
            bool mbIsControllerInitFinishedPending;
            bool mbIsControllerPrepareShutdownFinished;
            bool mbIsControllerPrepareShutdownFinishedPending;
            std::vector<std::shared_ptr<CSubController>> mSubCtrlList;
            void addSubCtrl( std::shared_ptr<CSubController> subCtrl );
            void removeSubCtrl ( std::shared_ptr<CSubController> subCtrl );
            virtual void update() override;
        };
    }
}

#endif // CCONTROLLER_H
