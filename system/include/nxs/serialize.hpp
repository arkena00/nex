#ifndef SERIALIZE_H_NXS
#define SERIALIZE_H_NXS

#include <nxs/encoder/cereal_json.hpp>

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
        return nds::encoder<nxs::encoders::cereal_json>::encode(t);
    }

    template<class T, class Linear_Type>
    T unserialize(const Linear_Type& data)
    {
        return nds::encoder<nxs::encoders::cereal_json>::decode<T>(data);
    }
} // nxs

#endif // SERIALIZE_H_NXS
