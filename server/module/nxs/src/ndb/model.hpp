#ifndef MODEL_H_NDB
#define MODEL_H_NDB

#include <ndb/engine/setup.hpp>
#include <ndb/table_option.hpp>
#include <string>
#include <vector>

namespace ndb
{
    template<class Engine> class table;
    template<class Engine> class field_base;

    class model_base
    {
    public:
        virtual std::string str() const { return ""; }
        virtual ~model_base() {}
    };

    template<class Engine>
    class model : public model_base
    {
        friend class table<Engine>;
        friend class field_base<Engine>;

    public:
        typename setup<Engine>::expression_type _data;

        void table_add(const table<Engine>& t);
        void table_option_add(const table_option<Engine>& t, const std::string& name);
        void field_add(const field_base<Engine>& f);

    public:
        model() = default;

        void make(const ndb::engine<>&) const;
        virtual std::string str() const override;
    };
} // ndb

#include "model.tpp"

#endif // MODEL_H_NDB

