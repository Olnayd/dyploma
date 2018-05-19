#include "IController.h"
#include <QDebug>
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
    qDebug() << "[" << getName() << "]" << common::helper::toString(step);
}
