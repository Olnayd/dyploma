#ifndef ECONTROLLERPROCESSINGSTEP_H
#define ECONTROLLERPROCESSINGSTEP_H

enum class EControllerProcessingStep
{
    e_Idle,
    e_Initialising,
    e_Initialised,
    e_Processing,
    e_PreparingShutdown,
    e_PrepareShutdownFinished,

    e_InitialisingError,
    e_PreparingShutdownError,

};

#endif // ECONTROLLERPROCESSINGSTEP_H
