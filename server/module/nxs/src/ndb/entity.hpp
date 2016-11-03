#ifndef ENTITY_H_NDB
#define ENTITY_H_NDB

#include <ndb/engine/setup.hpp>
#include <ndb/result.hpp>

namespace ndb
{
    template<class T, class Engine = setup<>::engine>
    class entity
    {
    protected:
        int _id;

    private:
        bool _exist;

    public:
        entity(const line<Engine>&);
        entity(int id);

        int id() const;
        bool exist() const;
        line<Engine> data();

        static std::vector<T> get();
        static result<Engine> add(expression<Engine>& expr);
        static result<Engine> del(int id);
    };
} // ndb

#include "entity.tpp"

#endif // ENTITY_H_NDB

