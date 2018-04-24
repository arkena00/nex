namespace nxs{namespace network
{
    template<size_t S> buffer<S>::buffer() : _data_size(0) {}

    template<size_t S> std::array<char, S>* buffer<S>::address() { return &_data; }
    template<size_t S> const char* buffer<S>::data() const { return _data.data(); }
    template<size_t S> constexpr size_t buffer<S>::capacity() const { return S; }
    template<size_t S> void buffer<S>::reserve(size_t n) { _data_size = n; }
    template<size_t S> size_t buffer<S>::size() const { return _data_size; }
}} // nxs::network
