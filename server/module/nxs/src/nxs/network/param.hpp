#ifndef NETWORK_PARAM_H_NXS
#define NETWORK_PARAM_H_NXS

#include <nxs/share.hpp>
#include <nxs/network/header.hpp>
#include <nds/encoder.hpp>
#include <map>
#include <string>

namespace nxs
{
    class NXS_SHARED param
    {
    public:
        enum modc { optional, require, overwrite };

    private:
        std::string _name;
        std::map<int, std::string> _value;
        modc _mod;
        std::string _format;

    public:
        param() = default;
        param(const std::string& name,
              const param::modc param_mod = modc::optional,
              const std::string& value = "",
              const std::string& format = "");
        param(const std::string& name, const std::string& value);
        ~param();

        std::string& operator[](int index);

        const std::string& name() const;
        template<class T = std::string>
        T value(int index = 0) const;

        const std::string& format() const;
        const std::map<int, std::string>& value_list() const;
        modc mod() const;
        size_t size() const;
        void add(const std::string& value);

        bool is_overwrite() const;
        bool is_required() const;
    };

    template<class T>
    T param::value(int index) const
    {
        return nds::encoder<>::decode<T, nxs::param>(_value.at(index));
    }



    // param_list
    class NXS_SHARED param_list
    {
        using Param_List = std::map<std::string, nxs::param>;

    public:
        typedef Param_List::const_iterator const_iterator;
        typedef Param_List::iterator iterator;

    private:
        Param_List _list;

    public:
        param_list() = default;

        nxs::param& operator[](const std::string& name);
        const_iterator begin() const;
        const_iterator end() const;
        iterator begin();
        iterator end();

        void add(const param&);
        void clear();
        size_t size() const;
        bool exist(const std::string& name) const;
        bool exist(header::code h_code) const;
        void parse(const std::string& str_param_list);
    };
} // nxs

#endif // NETWORK_PARAM_H_NXS
