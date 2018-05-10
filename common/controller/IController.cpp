#include "IController.h"

#include "common/helper/commonhelper.h"

using namespace common::controller;

IController::IController()
: eProcessingStep( EControllerProcessingStep::e_Idle )
{

}

void IController::setProcessingStep(EControllerProcessingStep step)
{
    eProcessingStep = step;
    notify();
}
