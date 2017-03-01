namespace nds
{
    // encode for Encoder class
    template<class Encoder, class T>
    std::enable_if_t<std::is_base_of<encoder, Encoder>::value, typename Encoder::linear_type>
    encoder::encode(const T& in)
    {
        return Encoder::encode(in);
    }

    // encode T with T::linear_type
    template<class T>
    typename T::linear_type encode(const T& in)
    {
        return encode<T::linear_type, encoders::global>(in);
    }

    // decode for Encoder class
    template<class T, class Encoder, size_t Version, class Linear_Type>
    std::enable_if_t<std::is_base_of<encoder, Encoder>::value, T>
    encoder::decode(const Linear_Type& in)
    {
        return Encoder::template decode<T>(in);
    }
} // nds
