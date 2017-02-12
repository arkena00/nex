#ifndef ENGINE_ENGINE_H_NDB
#define ENGINE_ENGINE_H_NDB

#include <ndb/engine/setup.hpp>
#include <map>
#include <string>
#include <memory>

namespace ndb
{
    class model_base;
    template<class Engine> class query;
    template<class Engine> class result;

    template<class Engine>
    class engine
    {
    private:
        static std::map<std::string, std::unique_ptr<engine<Engine>>> connect_list_;
        static std::string current_;
        static std::string path_;
        static const ndb::model<Engine>* model_default_;

        std::string _identifier;

    protected:
        bool _init = false;

        engine(const std::string& identifier);

        virtual bool connect() = 0;
        virtual void close() = 0;

    public:
        engine(const engine&) = delete;
        engine& operator=(const engine&) = delete;
        virtual ~engine();

        const std::string& identifier() const;
        std::string path() const;
        bool exist() const;
        bool is_init() const;

        virtual ndb::result<Engine> exec(ndb::query<Engine>& q) const = 0;
        virtual ndb::result<Engine> exec(const typename setup<Engine>::expression_type& q) const = 0;

        static const engine& get(const std::string& identifier = current_);
        static void set(const std::string& identifier);
        static const ndb::model<Engine>& model();
        static void model_add(const ndb::model<Engine>& m);
        static void path_set(const std::string& path);
        static const engine& connect(const std::string& identifier);
    };
} // ndb

#include "engine.tpp"

#endif // ENGINE_ENGINE_H_NDB
