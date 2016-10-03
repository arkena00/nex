#ifndef NDS_NDS_H_NXS
#define NDS_NDS_H_NXS

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>

#include <nxs/network/header.hpp>

#include <iostream>

namespace nds
{
    namespace encoders { class custom; }

    class encoder
    {
    public:
        template<typename Enc, typename T>
        static void encode(Enc& e, T& t, unsigned int version = 0)
        {
            t.encode(e, version);
        }

        // specialized for custom encoding (parsing)
        template<class Encoder = encoders::custom, class T, class Linear_type>
        static void decode(const Linear_type& in, T& out);
    };

    template<class Encoder, class T>
    typename Encoder::Linear_type encode(T& data)
    {
        Encoder enc;
        return enc.encode(data);
    }

    template<class Encoder, class T, class Linear_type>
    T decode(Linear_type& data)
    {
        Encoder enc;
        return enc.decode<T>(data);
    }






    namespace encoders
    {
        class custom;

        class boost_text
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


//encoder & a & b & c;

//boost::archive::text_oarchive
#endif // NDS_NDS_H_NXS
