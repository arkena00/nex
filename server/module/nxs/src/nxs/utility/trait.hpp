#ifndef UTILITY_TRAIT_H_NXS
#define UTILITY_TRAIT_H_NXS

#include <type_traits>

namespace nxs
{
    class enabler {};

    template<bool Condition>
    using enable_if = std::enable_if_t<Condition, enabler>;


    namespace trait
    {
        template<class> struct sfinae_true : std::true_type {};

        // is_serializable
        namespace detail
        {
          template<class T> static auto is_serializable(int) -> sfinae_true<decltype(std::declval<T>().serialize())>;
          template<class> static auto is_serializable(char) -> std::false_type;
        } // detail
        template<class T> struct is_serializable : decltype(detail::is_serializable<T>(0)){};

    } // trait
} // nxs

#endif // UTILITY_TRAIT_H_NXS
