#ifndef NDS_ENCODER_H_NDS
#define NDS_ENCODER_H_NDS

#include <nxs/share.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>

#include <iostream>

namespace nds
{
    namespace encoders { class global; }

    class NXS_SHARED encoder
    {
    public:
        template<typename Enc, typename T>
        static void encode(Enc& e, T& t, unsigned int version = 0)
        {
            t.encode(e, version);
        }


        template<class Encoder = encoders::global, class Linear_type, class T>
        static void decode(const Linear_type& in, T& out);

        template<class T, class Encoder = encoders::global, size_t Version = 1, class Linear_type>
        static T decode(const Linear_type& in);

        template<class Encoder = encoders::global, class T, class Linear_type>
        static void encode(const T& in, Linear_type& out);

        template<class Linear_type, class Encoder = encoders::global, size_t Version = 1, class T>
        static Linear_type encode(const T& in);
    };


    template<class Encoder, class T>
    typename Encoder::Linear_type NXS_SHARED encode(T& data)
    {
        Encoder enc;
        return enc.encode(data);
    }

    template<class Encoder, class T, class Linear_type>
    T NXS_SHARED decode(Linear_type& data)
    {
        Encoder enc;
        return enc.decode(data);
    }


    namespace encoders
    {
        class NXS_SHARED boost_text
        {
        public:
            using Linear_type = std::string;

            template<class T>
            Linear_type encode(T& t)
            {
                std::stringstream _buffer;
                boost::archive::text_oarchive ar(_buffer);
                encoder::encode(ar, t);
                return _buffer.str();
            }

            template<class T>
            T decode(const Linear_type& data)
            {
                T t;
                std::stringstream _buffer(data);
                boost::archive::text_iarchive ar(_buffer);
                encoder::encode(ar, t);
                return t;
            }
        };

    } // encoders











    struct custom
    {
        int u;
        custom() : u(999) {}
        friend class access;
        template<class E> void encode(E& enc, unsigned int version) { enc & u; }
    };

    struct test
    {
        int a;
        std::string b;
        custom c;

        friend class access;
        template<class E> void encode(E& enc, unsigned int version) { enc & a & b & c; }

        test() : a(555), b("test") {}

    };
} // nds

#endif // NDS_ENCODER_H_NDS
