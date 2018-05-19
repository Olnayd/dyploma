#include "version.h"

using namespace common;

version::version( int major_, int minor_)
    : major(major_)
    , minor(minor_)
{

}

version::version()
    : major(-1)
    , minor(-1)
{

}

