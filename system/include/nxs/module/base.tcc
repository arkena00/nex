#include <nxs/os/module.hpp>
#include <nxs/network/request.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace nxs
{
    template<class T> NXS_SHARED std::map<int, std::unique_ptr<base_module<T>>> base_module<T>::load_list_id_;
    template<class T> NXS_SHARED std::map<std::string, int> base_module<T>::module_id_;

    // protected:
    template<class T>
    base_module<T>::base_module(int id) : db::entity<T>(id),
        m_path("./" + T::name_ + "/"),
        m_is_loaded(0)
    {
        hydrate(Entity::data());
    }
    template<class T>
    base_module<T>::base_module(const db::line& data) : db::entity<T>(data),
        m_path("./" + T::name_ + "/"),
        m_is_loaded(0)
    {
        hydrate(Entity::data());
    }

    template<class T>
    void base_module<T>::hydrate(const db::line& data)
    {
        const auto& m = T::db_ref;
        db::result res = db::query() << (m.all()) << (m.id == id());
        m_name = res[m.name];
        m_image = res[m.image];
        m_description = res[m.description];
        m_author = res[m.author];
        m_tag = res[m.tag];
        m_ext = res[m.ext];

        m_path = "./" + T::name_ + "/";
        std::string v_ext = ext();
        if (v_ext == "dl") v_ext = NXS_OS_SHARELIBEXT;
        if (fs::is_directory(m_path + name())) m_path = m_path + name() + "/";
        m_path = m_path + name() + T::ext_ + "." + v_ext;
    }


    template<class T>
    void base_module<T>::unload()
    {
        load_list_id_.erase(id());
        module_id_.erase(name());
        m_is_loaded = 0;
    }

    template<class T>
    template<class M_Type>
    void base_module<T>::store(std::unique_ptr<M_Type> m)
    {
        module_id_.insert(std::make_pair(m->name(), m->id())); // link name to id
        load_list_id_.insert(std::make_pair(m->id(), std::move(m))); // move module to load_list
    }

    // public:
    template<class T> int base_module<T>::id() const { return Entity::id(); }
    template<class T> const std::string& base_module<T>::name() const { return m_name; }
    template<class T> const std::string& base_module<T>::image() const { return m_image; }
    template<class T> const std::string& base_module<T>::description() const { return m_description; }
    template<class T> const std::string& base_module<T>::author() const { return m_author; }
    template<class T> const std::string& base_module<T>::tag() const { return m_tag; }
    template<class T> const std::string& base_module<T>::ext() const { return m_ext; }

    template<class T> const std::string& base_module<T>::path() const { return m_path; }
    template<class T> bool base_module<T>::is_loaded() const { return m_is_loaded; }

    template<class T> void base_module<T>::data_set(const std::string& key, const std::string& value)
    {
        const auto& md = db::nex.module_data;
        db::result res = db::query() + (md.id = id(), md.key = key, md.value = value);
    }

    template<class T> std::string base_module<T>::data(const std::string& key) const
    {
        return "";
    }

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////             STATIC             ////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    template<class T>
    int base_module<T>::execute(nxs::nex& nex)
    {
        return get(nex.input().module_name()).process(nex);
    }


    template<class T>
    std::vector<T> base_module<T>::get()
    {
        return db::entity<T>::get();
    }
    template<class T>
    base_module<T>& base_module<T>::get(int id)
    {
        if (!is_loaded(id)) nxs_error << T::name_ << " is not loaded :" + id;
        return *load_list_id_.at(id).get();
    }
    template<class T>
    base_module<T>& base_module<T>::get(const std::string& name)
    {
        if (!is_loaded(name)) nxs_error << T::name_ << " is not loaded :" + name;
        return get(module_id_.at(name));
    }

    template<class T>
    bool base_module<T>::is_loaded(int id)
    {
        if (load_list_id_.count(id) > 0) return 1;
        return 0;
    }
    template<class T>
    bool base_module<T>::is_loaded(const std::string& name)
    {
        if (module_id_.count(name) > 0) return 1;
        return 0;
    }

} // nxs

