namespace ndb
{
    template<class Engine>
    void query<Engine>::clear() { _expression.clear(); }

    template<class Engine>
    typename setup<Engine>::expression_type query<Engine>::native() const { return _expression.native(); }

    template<class Engine>
    query<Engine>::operator ndb::result<Engine>()
    {
        return exec();
    }

    template<class Engine>
    query<Engine>& query<Engine>::operator<<(const ndb::expression<Engine>& expr)
    {
        _expression.append(expr);
        return *this;
    }

    template<class Engine>
    query<Engine>& query<Engine>::operator+(auto&& expr)
    {
        expr._type = expression<Engine>::add;
        _expression.append(expr);
        return *this;
    }

    template<class Engine>
    query<Engine>& query<Engine>::operator-(ndb::expression<Engine>& expr)
    {
        expr._type = expression<Engine>::del;
        _expression.append(expr);
        return *this;
    }

    template<class Engine>
    ndb::result<Engine> query<Engine>::exec()
    {
        return Engine::get().exec(*this);
    }

    template<class Engine>
    ndb::result<Engine> query<Engine>::result()
    {
        return Engine::get().exec(*this);
    }

    template<class Engine>
    ndb::result<Engine> query<Engine>::exec(const ndb::expression<Engine>& expr)
    {
        ndb::query<Engine> q;
        q << expr;
        return Engine::get().exec(q);
    }
} // nxs::db
