namespace nxs
{
    template<class H> bool request_base::header_exist() const { return _header_list.count(H::id()); }

    template<class H> void request_base::header_exist_check() const
    {
        if (!header_exist<H>()) nxs_error(errc::system, "header does not exist in request : " + std::string(H::name()));
    }

    template<class H, class T>
    void request_base::header_add(T value)
    {
        if (header_exist<H>()) header<H>().add(value);
        else _header_list.insert(std::make_pair(H::id(), std::make_unique<H>(value)));
    }

    template<class H> H& request_base::header() { return *static_cast<H*>(_header_list[H::id()].get()); }

    template<class H>
    auto request_base::header_value(size_t index) const
    {
        header_exist_check<H>();
        return static_cast<H*>(_header_list[H::id()].get())->value(index);
    }

    template<class H>
    auto request_base::header_value() const
    {
        header_exist_check<H>();
        return static_cast<H*>(_header_list[H::id()].get())->value();
    }
} // nxs
