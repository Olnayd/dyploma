#include "CSubController.h"

using namespace common::controller;

void CSubController::startInitialization()
{
    setProcessingStep(EControllerProcessingStep::e_Initialising);
    if( init() )
        setProcessingStep(EControllerProcessingStep::e_Initialised);
}

void CSubController::startController()
{
    setProcessingStep(EControllerProcessingStep::e_Processing);
}

void CSubController::startPrepareShutdown()
{
    setProcessingStep(EControllerProcessingStep::e_PreparingShutdown);
    if( init() )
        setProcessingStep(EControllerProcessingStep::e_PrepareShutdownFinished);
}

void CSubController::initFinished(bool result)
{
    if (!result) setProcessingStep(EControllerProcessingStep::e_InitialisingError);
    else setProcessingStep(EControllerProcessingStep::e_Initialised);
}

void CSubController::prepareShutdownFinished(bool result)
{
    if (!result) setProcessingStep(EControllerProcessingStep::e_PreparingShutdownError);
    else setProcessingStep(EControllerProcessingStep::e_PrepareShutdownFinished);
}
