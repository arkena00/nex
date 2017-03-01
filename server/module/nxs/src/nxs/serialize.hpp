#ifndef SERIALIZE_H_NXS
#define SERIALIZE_H_NXS

#include <nds/encoder/boost_text.hpp>

// macro
#define nxs_serialize(S) \
        friend class boost::serialization::access; \
        template<class Encoder> \
        void serialize(Encoder& enc, const unsigned int version) \
        { \
            enc & S; \
        } \

namespace nxs
{
    template<class T>
    auto serialize(const T& t)
    {
        return nds::encoder::encode<nds::encoders::boost_text>(t);
    }

    template<class T, class Linear_Type>
    T unserialize(const Linear_Type& data)
    {
        return nds::encoder::decode<T, nds::encoders::boost_text>(data);
    }
} // nxs

#endif // USER_H_NXS
