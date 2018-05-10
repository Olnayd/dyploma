#include "commonhelper.h"

namespace common
{
    namespace helper
    {
        const char* toString(EControllerProcessingStep step)
        {
            switch(step)
            {
                case EControllerProcessingStep::e_Idle: return "e_Idle"; break;
                case EControllerProcessingStep::e_Initialising: return "e_Initialising"; break;
                case EControllerProcessingStep::e_Initialised: return "e_Initialised"; break;
                case EControllerProcessingStep::e_Processing: return "e_Processing"; break;
                case EControllerProcessingStep::e_PreparingShutdown: return "e_PreparingShutdown"; break;
                case EControllerProcessingStep::e_PrepareShutdownFinished: return "e_PrepareShutdownFinished"; break;

                case EControllerProcessingStep::e_InitialisingError: return "e_InitialisingError"; break;
                case EControllerProcessingStep::e_PreparingShutdownError: return "e_PreparingShutdownError"; break;
                default: return ""; break;
            }

        }
    }
}
