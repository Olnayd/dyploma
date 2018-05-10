#ifndef CSUBCONTROLLER_H
#define CSUBCONTROLLER_H

#include "IController.h"
#include "EControllerProcessingStep.h"



namespace common
{
    namespace controller
    {
        class CSubController : public IController
        {
        public:
            virtual void initFinished(bool result) override final;
            virtual void prepareShutdownFinished(bool result) override final;

        public:
            virtual void startInitialization() override final;
            virtual void startController() override final;
            virtual void startPrepareShutdown()  override final;
        };
    }

}




#endif // CSUBCONTROLLER_H
