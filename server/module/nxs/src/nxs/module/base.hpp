#ifndef MODULE_BASE_H_NXS
#define MODULE_BASE_H_NXS

#include <nxs/core.hpp>
#include <nxs/database.hpp>

#include <string>
#include <map>
#include <memory>

namespace nxs
{
    template<class T>
    class NXS_SHARED base_module : public db::entity<T>
    {
        using Entity = db::entity<T>;
        using Base_module = base_module<T>;

    private:
        std::string _name;
        std::string _image;
        std::string _description;
        std::string _author;
        std::string _tag;
        std::string _ext;
        std::string _path;

    protected:
        static std::map<int, std::unique_ptr<Base_module>> load_list_id_;
        static std::map<std::string, int> module_id_;

        bool _is_loaded;

    private:
        void hydrate(const db::line&);

    protected:
        base_module(int id);
        base_module(const db::line&);

        virtual bool load() = 0;
        virtual void unload();
        virtual int process(nxs::nex& nex) = 0;

        template<class M_Type> static void store(std::unique_ptr<M_Type> ptr);

    public:
        int id() const;
        const std::string& name() const;
        const std::string& image() const;
        const std::string& description() const;
        const std::string& author() const;
        const std::string& tag() const;
        const std::string& ext() const;
        const std::string& path() const;
        bool is_loaded() const;

        void data_set(const std::string& key, const std::string& value);
        std::string data(const std::string& key) const;

        static int execute(nxs::nex& nex);
        static std::vector<T> get();
        static Base_module& get(int id);
        static Base_module& get(const std::string& name);
        static bool is_loaded(int id);
        static bool is_loaded(const std::string& name);
    };
} // nxs

#include "base.tpp"

#endif // MODULE_BASE_H_NXS
