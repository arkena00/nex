namespace ndb
{
    template<class T, class Engine>
    entity<T, Engine>::entity(const line<Engine>& data) :
        _id(data[T::db_ref.id]),
        _exist(true)
    {}

    template<class T, class Engine>
    entity<T, Engine>::entity(int id) :
        _id(id),
        _exist(false)
    {}

    template<class T, class Engine>
    int entity<T, Engine>::id() const { return _id; }

    template<class T, class Engine>
    bool entity<T, Engine>::exist() const { return _exist; }

    template<class T, class Engine>
    line<Engine> entity<T, Engine>::data()
    {
        const auto& table = T::db_ref;
        result<Engine> res = query<Engine>() << table.all() << (table.id == _id);
        if (res.size() > 0) _exist = true;
        return res[0];
    }

    template<class T, class Engine>
    std::vector<T> entity<T, Engine>::get()
    {
        std::vector<T> vec;
        result<Engine> res = query<Engine>() << (T::db_ref.all());
        for(auto& item : res) vec.push_back(T(item));
        return vec;
    }

    template<class T, class Engine>
    result<Engine> entity<T, Engine>::add(expression<Engine>& expr)
    {
        return query<Engine>() + (expr);
    }

    // add entity with secified name and return id, field name must exist
    template<class T, class Engine>
    int entity<T, Engine>::add(const std::string& name)
    {
        const auto& t = T::db_ref;
        result<Engine> res = query<Engine>() + (t.name = name);
        return res.add_id();
    }

    template<class T, class Engine>
    result<Engine> entity<T, Engine>::del(int id)
    {
        return query<Engine>() - (T::db_ref.id == id);
    }
} // ndb
