#include <nxs/error.hpp>
#include <nxs/utility/reflector.hpp>
#include <nxs/utility/trait.hpp>
#include <iostream>

namespace nxs
{
    // initialize headers
    template<unsigned char H_id>
    void header::init()
    {
        using H = typename headers::detail::initializer<static_cast<header::code>(H_id)>::type;
        code_.insert(std::make_pair(H::name(), H::id()));
        list_.push_back(H::id());
        reflector_list_.push_back(&reflector<header, H>);
        init<H_id + 1>(); // if you get error here, the class for header::code enum is not found
    }

    // single value header
    template<class T>
    header_basic<T>::header_basic(header::code id, const std::string& name) :
        header(id, name)
    {}
    template<class T>
    header_basic<T>::header_basic(header::code id, const std::string& name, const T& value) :
        header(id, name)
    { add(value); }

    template<class T>
    void header_basic<T>::add_linear(const header::linear_type& linear_data) { _value = nds::encoder::decode<T, header>(linear_data); }

    template<class T>
    header::linear_type header_basic<T>::value_linear() { return nds::encoder::encode<header::linear_type, header>(_value); }

    template<class T>
    header& header_basic<T>::operator=(const header& other)
    {
        _value = static_cast<const header_basic<T>&>(other)._value;
        return *this;
    }

    template<class T>
    void header_basic<T>::add(const T& value) { _value = value; }

    template<class T> const T& header_basic<T>::value() const { return _value; }

    // multi value header
    template<class T>
    header_basic<std::vector<T>>::header_basic(header::code id, const std::string& name) :
        header(id, name)
    {}
    template<class T>
    header_basic<std::vector<T>>::header_basic(header::code id, const std::string& name, const T& value) :
            header(id, name)
    { add(value); }

    template<class T>
    void header_basic<std::vector<T>>::add_linear(const header::linear_type& linear_data) { _value.push_back(nds::encoder::decode<T, header>(linear_data)); }

    template<class T>
    header::linear_type header_basic<std::vector<T>>::value_linear() { return nds::encoder::encode<header::linear_type, header>(_value); }

    template<class T>
    header& header_basic<std::vector<T>>::operator=(const header& other)
    {
        _value = static_cast<const header_basic<std::vector<T>>&>(other)._value;
        return *this;
    }

    template<class T>
    void header_basic<std::vector<T>>::add(const T& value) { _value.push_back(value); }

    template<class T>
    const T& header_basic<std::vector<T>>::value(size_t index) const
    {
        if (index >= _value.size()) throw nxs_error << "value index" << index << "out of range for header" << name();
        return _value[index];
    }
    template<class T>
    size_t header_basic<std::vector<T>>::size() const { return _value.size(); }

} // nxs
