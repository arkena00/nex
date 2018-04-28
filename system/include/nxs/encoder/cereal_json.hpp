#ifndef ENCODER_CEREAL_H_NDS
#define ENCODER_CEREAL_H_NDS

#include <sstream>
#include <nds/encoder.hpp>

#include <cereal/archives/json.hpp>

#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>

namespace nxs
{
    namespace encoders
    {
        class cereal_json : nds::encoder<cereal_json>
        {
        public:
            using linear_type = std::string;

            template<class T>
            static linear_type encode(const T& t)
            {
                std::stringstream buffer;
                ::cereal::JSONOutputArchive ar(buffer);
                ar << t;
                return buffer.str();
            }
            static linear_type encode(const char* t) { return t; }

            template<class T>
            static T decode(const linear_type& data)
            {
                std::stringstream buffer(data);
                ::cereal::JSONInputArchive ar(buffer);
                T res;
                ar >> res;
                return res;
            }
        };
    } // encoders
} // nds

#endif // ENCODER_CEREAL_H_NDS
