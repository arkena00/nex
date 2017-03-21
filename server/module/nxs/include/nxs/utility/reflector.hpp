#ifndef UTILITY_REFLECTOR_H_NXS
#define UTILITY_REFLECTOR_H_NXS

namespace nxs
{
    template<class Base_T, class T>
    Base_T* reflector()
    {
        return new T;
    }
}

#endif // UTILITY_REFLECTOR_H_NXS
