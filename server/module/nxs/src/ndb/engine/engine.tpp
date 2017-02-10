#include <ndb/error.hpp>
#include <ndb/model.hpp>
#include <fstream>

namespace ndb
{
    template<class Engine> std::map<std::string, std::unique_ptr<engine<Engine>>> engine<Engine>::connect_list_;
    template<class Engine> std::string engine<Engine>::current_ = "";
    template<class Engine> std::string engine<Engine>::path_ = setup<setup<>::engine>::path;
    template<class Engine> const model<Engine>* engine<Engine>::model_default_ = nullptr;

    template<class Engine>
    engine<Engine>::engine(const std::string& identifier) :
        _identifier(identifier),
        _created(false)
    {}

    template<class Engine>
    engine<Engine>::~engine() {}

    template<class Engine>
    const std::string& engine<Engine>::identifier() const { return _identifier; }

    template<class Engine>
    std::string engine<Engine>::path() const
    {
        return path_ + _identifier + setup<setup<>::engine>::ext;
    }

    template<class Engine>
    bool engine<Engine>::exist() const
    {
        if (std::ifstream(path())) return true;
        if (!std::ofstream(path())) ndb_error("path is inaccessible : " + path_);
        return false;
    }

    template<class Engine>
    bool engine<Engine>::is_created() const { return _created; }

    template<class Engine>
    const engine<Engine>& engine<Engine>::get(const std::string& identifier)
    {
        if (!connect_list_.count(identifier)) ndb_error("identifier not found : " + std::string(identifier));
        return *connect_list_[identifier].get();
    }

    template<class Engine>
    void engine<Engine>::set(const std::string& identifier)
    {
        current_ = identifier;
    }

    template<class Engine>
    const ndb::model<Engine>& engine<Engine>::model()
    {
        if (model_default_ == nullptr) ndb_error("no default model set");
        return *model_default_;
    }

    template<class Engine>
    void engine<Engine>::model_add(const ndb::model<Engine>& m)
    {
        model_default_ = &m;
    }

    template<class Engine>
    void engine<Engine>::path_set(const std::string& path)
    {
        path_ = path;
    }

    template<class Engine>
    const engine<Engine>& engine<Engine>::connect(const std::string& identifier)
    {
        current_ = identifier;
        auto engine_ptr = std::make_unique<Engine>(identifier);
        if (!engine_ptr->connect()) ndb_error("database connexion failed");
        connect_list_.insert(std::make_pair(identifier, std::move(engine_ptr)));
        return get(identifier);
    }
} // ndb
