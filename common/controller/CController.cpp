#include "CController.h"

#include <algorithm>

using namespace common::controller;

CController::CController()
    : mbIsControllerInitFinished{false}
    , mbIsControllerInitFinishedPending{false}
    , mbIsControllerPrepareShutdownFinished{false}
    , mbIsControllerPrepareShutdownFinishedPending{false}
{

}

void CController::startController()
{
    for ( auto subCtrl : mSubCtrlList) subCtrl->startController();
    setProcessingStep(EControllerProcessingStep::e_Processing);
}


void CController::startInitialization()
{
    setProcessingStep(EControllerProcessingStep::e_Initialising);
    if( init() )
    {
        mbIsControllerInitFinished = true;
        for ( auto subCtrl : mSubCtrlList) subCtrl->startInitialization();
    }

    if(areSubCtrlFinishedInitialization() && !mbIsControllerInitFinishedPending)
    {
        mbIsControllerInitFinishedPending = true;
        setProcessingStep(EControllerProcessingStep::e_Initialised);
    }

}

void CController::initFinished(bool result)
{
    if (!result) setProcessingStep(EControllerProcessingStep::e_InitialisingError);
    else
    {
        mbIsControllerInitFinished = true;
        for ( auto subCtrl : mSubCtrlList) subCtrl->startInitialization();
        if(areSubCtrlFinishedInitialization() && !mbIsControllerInitFinishedPending)
        {
            mbIsControllerInitFinishedPending = true;
            setProcessingStep(EControllerProcessingStep::e_Initialised);
        }
    }
}

void CController::startPrepareShutdown()
{
    setProcessingStep(EControllerProcessingStep::e_PreparingShutdown);
    for ( auto subCtrl : mSubCtrlList) subCtrl->startPrepareShutdown();

    if(areSubCtrlFinishedPrepareShutdown() && !mbIsControllerPrepareShutdownFinishedPending)
    {
        mbIsControllerPrepareShutdownFinishedPending = true;
        if( prepareShutdown() )
        {
            mbIsControllerPrepareShutdownFinished = true;
            setProcessingStep(EControllerProcessingStep::e_PrepareShutdownFinished);
        }

    }
}

void CController::prepareShutdownFinished(bool result)
{
    if (!result) setProcessingStep(EControllerProcessingStep::e_PreparingShutdownError);
    else setProcessingStep(EControllerProcessingStep::e_PrepareShutdownFinished);
}

void CController::addSubCtrl( std::shared_ptr<CSubController> subCtrl )
{
    mSubCtrlList.push_back(subCtrl);
    subCtrl->attach(this);
}

void CController::removeSubCtrl ( std::shared_ptr<CSubController> subCtrl )
{
    auto ctrlIt = std::find(mSubCtrlList.begin(),mSubCtrlList.end(),subCtrl);
    if( ctrlIt != mSubCtrlList.end())
    {
        mSubCtrlList.erase(ctrlIt);
        subCtrl->dettach(this);
    };
}

void CController::update()
{
    if ( eProcessingStep == EControllerProcessingStep::e_Initialising)
    {
         if(areSubCtrlFinishedPrepareShutdown() && mbIsControllerInitFinished)
             setProcessingStep(EControllerProcessingStep::e_Initialised);
    }
    if ( eProcessingStep == EControllerProcessingStep::e_PreparingShutdown)
    {
         if(areSubCtrlFinishedPrepareShutdown() && !mbIsControllerPrepareShutdownFinishedPending)
         {
             mbIsControllerPrepareShutdownFinishedPending = true;
             if( prepareShutdown() )
             {
                 mbIsControllerPrepareShutdownFinished = true;
                 setProcessingStep(EControllerProcessingStep::e_PrepareShutdownFinished);
             }
         }
    }
}

bool CController::areSubCtrlFinishedInitialization()
{
    bool result = true;
    for ( auto subCtrl : mSubCtrlList)
    {
        if(subCtrl->eProcessingStep != EControllerProcessingStep::e_Initialised)
            result = false;
    }
    return result;
}

bool CController::areSubCtrlFinishedPrepareShutdown()
{
    bool result = true;
    for ( auto subCtrl : mSubCtrlList)
    {
        if(subCtrl->eProcessingStep != EControllerProcessingStep::e_PrepareShutdownFinished)
            result = false;
    }
    return result;
}
