#ifndef NETWORK_HEADER_H_NXS
#define NETWORK_HEADER_H_NXS

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <nds/encoder.hpp>
#include <nxs/setup/request.hpp>
#include <nxs/os/share.hpp>

namespace nxs
{
    namespace network { class nex; }

    class NXS_SHARED header
    {
    public:
        using linear_type = setup<request>::linear_type;

        enum code : unsigned char // header init and process executed in enum order
        {
            user_name = 0,
            data_size,
            data_target,
            size_
        };

        static std::vector<code> list_;
        static std::map<std::string, code> code_;
        static std::vector<std::function<header*()>> reflector_list_;

    private:
        header::code _id;
        std::string _name;

    protected:
        header(header::code id, const std::string& name);

    public:
        header::code id() const;
        const std::string& name() const;

        virtual void add_linear(const linear_type& value) = 0;
        virtual linear_type value_linear() = 0;

        virtual header& operator=(const header&) = 0;

        virtual void preprocess(network::nex&) {}
        virtual void process(network::nex&) {}

        template<unsigned char H = 0>
        static void init();

        static void preprocess_all(network::nex&);
        static void process_all(network::nex&);
        static std::unique_ptr<header> make(header::code id);
        static std::unique_ptr<header> make(const std::string& name);
    };
    template<> void header::init<header::size_>();

    // single value header
    template<class T>
    class header_basic : public header
    {
    private:
        T _value;

    public:
        header_basic(header::code id, const std::string& name);
        header_basic(header::code id, const std::string& name, const T& value);

        virtual void add_linear(const linear_type& linear_data);
        virtual linear_type value_linear();
        virtual header& operator=(const header&);

        void add(const T& value);
        const T& value() const;
    };

    // multi value header
    template<> template<class T>
    class header_basic<std::vector<T>> : public header
    {
    private:
        std::vector<T> _value;

    public:
        header_basic(header::code id, const std::string& name);
        header_basic(header::code id, const std::string& name, const T& value);

        virtual void add_linear(const linear_type& linear_data);
        virtual linear_type value_linear();
        virtual header& operator=(const header&);

        void add(const T& value);
        const T& value(size_t index = 0) const;
        size_t size() const;
    };



    namespace headers
    {
        namespace detail { template<int T> struct initializer {}; }

        class NXS_SHARED data_size : public header_basic<std::vector<size_t>>
        {
        private:
            size_t _data_index;
            size_t _data_offset;
        public:
            constexpr static header::code id() { return header::data_size; }
            constexpr static const char* name() { return "data_size"; }

            data_size() : header_basic(id() , name()) {}
            data_size(size_t value) : header_basic(id() , name(), value) { }

            virtual void preprocess(network::nex&) override;
            virtual void process(network::nex&) override;
        };
        namespace detail { template<> struct initializer<header::data_size> { using type = headers::data_size; }; }

        class NXS_SHARED data_target : public header_basic<std::vector<size_t>>
        {
        public:
            constexpr static header::code id() { return header::data_target; }
            constexpr static const char* name() { return "data_target"; }
            enum valuec { hdd = 8, memory = 9 };

            data_target() : header_basic(id() , name()) {}
            data_target(valuec value) : header_basic(id() , name(), value) {}
        };
        namespace detail { template<> struct initializer<header::data_target> { using type = headers::data_target; }; }

        class NXS_SHARED user_name : public header_basic<std::string>
        {
        public:
            constexpr static header::code id() { return header::user_name; }
            constexpr static const char* name() { return "user_name"; }

            user_name() : header_basic(id() , name()) {}
            user_name(const std::string& value) : header_basic(id() , name(), value) {}

            virtual void preprocess(network::nex&) override;
        };
        namespace detail { template<> struct initializer<header::user_name> { using type = headers::user_name; }; }

    } // headers
} // nxs

#include "header.tpp"

#endif // NETWORK_HEADER_H_NXS
