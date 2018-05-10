#include <memory>

#include "CRootComponent.h"

#include <QDebug>
#include "controller/CCourseCtrl.h"

enum class EController
{
    CourseController
};


void fillInControllers( std::vector< std::shared_ptr<common::controller::CController> >& toFillIn);

CRootComponent::CRootComponent()
    : mbIsApplicationReady{false}
    , mbIsPrepareShutdownReady{false}
{

}

void CRootComponent::requestBoot()
{
    qDebug() << "CRootComponent::requestBoot";
    fillInControllers(mCtrlList);
    for (auto& ctrl : mCtrlList)
    {
        ctrl->attach(this);
        ctrl->startInitialization();
    };
}

void CRootComponent::update()
{
    qDebug() << "CRootComponent::update";
    if (!mbIsApplicationReady)
    {
        if (areAllControllersInitialized())
        {
            mbIsApplicationReady = true;
            for (auto& ctrl : mCtrlList) ctrl->startController();
        }
    }
    else if(!mbIsPrepareShutdownReady)
    {
        if (areAllControllersFinishedPrepareShutdown()) mbIsPrepareShutdownReady = true;
    }
}

/*
 * Check metods
 */

bool CRootComponent::areAllControllersInitialized()
{
    bool result = true;
    for (auto& ctrl : mCtrlList)
    {
        if( ctrl->eProcessingStep != EControllerProcessingStep::e_Initialised)
            result = false;
    };
    return result;
}

bool CRootComponent::areAllControllersFinishedPrepareShutdown()
{
    bool result = true;
    for (auto& ctrl : mCtrlList)
    {
        if( ctrl->eProcessingStep != EControllerProcessingStep::e_PrepareShutdownFinished)
            result = false;
    };
        return result;
}

void fillInControllers( std::vector< std::shared_ptr<common::controller::CController> >& toFillIn)
{
    std::vector<EController> ctrlTypeList;
    ctrlTypeList.push_back(EController::CourseController);

    for ( auto ctrl : ctrlTypeList)
    {
        switch(ctrl)
        {
            case EController::CourseController:
            {
                std::shared_ptr<CCourseCtrl> courseCtrl = std::make_shared<CCourseCtrl>();
                std::shared_ptr<common::controller::CController> courseCtrlTest =
                        std::static_pointer_cast<common::controller::CController>(courseCtrl);
                toFillIn.push_back( courseCtrlTest );
            } break;
        }
    }
}
