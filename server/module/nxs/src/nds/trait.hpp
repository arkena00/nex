#ifndef NDS_TRAIT_H_NDS
#define NDS_TRAIT_H_NDS

#include <type_traits>

namespace nds
{
    // is_serializable
    namespace detail
    {
        template<class> struct sfinae_true : std::true_type {};
        template<class T, class Encoder> static auto is_serializable(int) -> sfinae_true<decltype(T().serialize())>;
        template<class, class> static auto is_serializable(char) -> std::false_type;
    } // detail
    template<class T, class Encoder> struct is_serializable : decltype(detail::is_serializable<T, Encoder>(0)){};

} // nds

#endif // NDS_TRAIT_H_NDS
