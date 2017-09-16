namespace nxs{namespace network
{
    // _value must be STL container

    template<class T>
    memory_data<T>::memory_data() : _value(T{}) {}

    // store pointer to data, lifetime of data is handled by user
    template<class T>
    memory_data<T>::memory_data(T& v) : _value(&v) {}
    template<class T>
    memory_data<T>::memory_data(const T& v) : _value(&v) {}

    // memory_data will store the value
    template<class T>
    memory_data<T>::memory_data(T&& t) : _value(std::move(t)) {}

    template<class T>
    T& memory_data<T>::value()
    {
        if (_value.index() == 0) return stdz::get<T>(_value);
        else if (_value.index() == 1) return *stdz::get<T*>(_value);
        else nxs_error << "bad memory_data variant access" << log::system;
    }

    template<class T>
    const T& memory_data<T>::value_const() const
    {
        if (_value.index() == 0) return stdz::get<T>(_value);
        else if (_value.index() == 1) return *stdz::get<T*>(_value);
        else if (_value.index() == 2) return *stdz::get<const T*>(_value);
        nxs_error << "bad memory_data variant access" << log::system;
    }

    template<class T>
    const char* memory_data<T>::name() const
    {
        return "memory";
    }

    template<class T>
    void memory_data<T>::add(const char* data_ptr, size_t data_size)
    {
        value().insert(value().begin() + transfer_size(), data_ptr, data_ptr + data_size);
        transfer_add(data_size);
    }

    template<class T>
    const char* memory_data<T>::ptr()
    {
        return value().data();
    }

    template<class T>
    size_t memory_data<T>::size() const
    {
        return value_const().size();
    }

    template<class T>
    void memory_data<T>::reserve(size_t n)
    {
        value().resize(n);
    }

    template<class T>
    data::target_code memory_data<T>::target() const
    {
        return data::memory;
    }

    // make memory_data from rvalue
    template<class T>
    std::shared_ptr<data> make_memory_data(T&& v)
    {
        return std::make_shared<memory_data<T>>(std::move(v));
    }

    // make memory_data from reference
    template<class T>
    std::shared_ptr<data> make_memory_data(const T& v)
    {
        return std::make_shared<memory_data<T>>(v);
    }

    template<class T>
    std::shared_ptr<data> make_memory_data(T& v)
    {
        return std::make_shared<memory_data<T>>(v);
    }
}} // nxs::network
