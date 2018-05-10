#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include "EControllerProcessingStep.h"
#include "common/observer/ISubject.h"

namespace common
{
    namespace controller
    {
        class   IController : public common::observer::ISubject
        {
        public:
            //interface fir final user
            IController();
            virtual bool init() = 0;
            virtual const char* getName() = 0;
            virtual bool prepareShutdown() = 0;

            //interface for wrapper
            virtual void initFinished(bool result) = 0;
            virtual void prepareShutdownFinished(bool result) = 0;

            virtual void startInitialization() = 0;
            virtual void startController() = 0;
            virtual void startPrepareShutdown()  = 0;


            void setProcessingStep(EControllerProcessingStep step);

        public:
            EControllerProcessingStep eProcessingStep;

        };
    }

}

#endif // ICONTROLLER_H
