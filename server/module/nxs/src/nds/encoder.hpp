#ifndef NDS_ENCODER_H_NDS
#define NDS_ENCODER_H_NDS

#include <nds/trait.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <nxs/share.hpp>

namespace nds
{
    namespace encoders { class global{}; }

    class NXS_SHARED encoder
    {
    public:
        //////// DECODE
        // decode in / out
        template<class Encoder = encoders::global, class Linear_Type, class T>
        static void decode(const Linear_Type& in, T& out);

        // decode for non Encoder class
        template<class T, class Encoder = encoders::global, size_t Version = 1, class Linear_Type>
        static std::enable_if_t<!std::is_base_of<encoder, Encoder>::value, T>
        decode(const Linear_Type& in);

        // decode for Encoder class
        template<class T, class Encoder, size_t Version = 1, class Linear_Type>
        static std::enable_if_t<std::is_base_of<encoder, Encoder>::value, T>
        decode(const Linear_Type& in);

        //////// ENCODE
        // encode in / out
        template<class Encoder, class T, class Linear_Type>
        static void encode(const T& in, Linear_Type& out);

        //
        template<class Linear_Type, class Encoder, size_t Version = 1, class T>
        static Linear_Type encode(const T& in);

        // encode for Encoder class
        template<class Encoder, class T>
        static std::enable_if_t<std::is_base_of<encoder, Encoder>::value, typename Encoder::linear_type>
        encode(const T& in);

        // encode for non Encoder class
        template<class Encoder, class T>
        static std::enable_if_t<!std::is_base_of<encoder, Encoder>::value, Encoder>
        encode(const T& in);

        // encode T with T::Linear_Type
        template<class T>
        static typename T::linear_type encode(const T& in);
    };
} // nds

#include "encoder.tpp"

#endif // NDS_ENCODER_H_NDS
