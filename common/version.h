#ifndef VERSION_H
#define VERSION_H

namespace common
{
    struct version
    {
       version( int major_, int minor_);

       int major;
       int minor;
    };

    inline bool operator==(const version& lhs, const version& rhs)
    {
        return ((lhs.major == rhs.major) && (lhs.major == rhs.major));
    }

    inline bool operator!=(const version& lhs, const version& rhs)
    {
        return !(lhs == rhs);
    }
}


#endif // VERSION_H
