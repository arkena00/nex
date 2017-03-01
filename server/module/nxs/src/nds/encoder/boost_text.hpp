#ifndef NDS_ENCODER_BOOST_TEXT_H_NDS
#define NDS_ENCODER_BOOST_TEXT_H_NDS

#include <nds/encoder.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>

namespace nds
{
    namespace encoders
    {
        class boost_text : encoder
        {
        public:
            using linear_type = std::string;

            template<class T>
            static linear_type encode(T& t)
            {
                std::stringstream buffer;
                boost::archive::text_oarchive ar(buffer);
                ar << t;
                return buffer.str();
            }
            static linear_type encode(const char* t) { return t; }

            template<class T>
            static T decode(const linear_type& data)
            {
                std::stringstream buffer(data);
                boost::archive::text_iarchive ar(buffer);
                T res;
                ar >> res;
                return res;
            }
        };
    } // encoders
} // nds


#endif // NDS_ENCODER_BOOST_TEXT_H_NDS
