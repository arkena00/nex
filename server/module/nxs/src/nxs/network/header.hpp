#ifndef NETWORK_HEADER_H_NXS
#define NETWORK_HEADER_H_NXS

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <memory>
#include <nds/encoder.hpp>
#include <nxs/setup/request.hpp>
#include <nxs/share.hpp>
#include <nxs/nex.hpp>
#include <nxs/network/io.hpp>

namespace nxs
{
    namespace network { template<io::type> class nex; }

    class NXS_SHARED header
    {
    public:
        using linear_type = setup<request>::linear_type;

        enum code : unsigned char // header init and process executed in enum order
        {
            req_id,
            user_name,
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
        virtual ~header() = default;

        header::code id() const;
        const std::string& name() const;

        virtual void add_linear(const linear_type& value) = 0;
        virtual linear_type value_linear() = 0;

        virtual header& operator=(const header&) = 0;

        virtual void preprocess(network::protocol&) {}
        virtual void process(network::protocol&) {}

        template<unsigned char H = 0>
        static void init();

        template<io::type IO_Type>
        static void preprocess_all(network::nex<IO_Type>&);
        template<io::type IO_Type>
        static void process_all(network::nex<IO_Type>&);
        static std::unique_ptr<header> make(header::code id);
        static std::unique_ptr<header> make(const std::string& name);
    };
    template<> void header::init<header::size_>();

    // single value header
    template<class T>
    class basic_header : public header
    {
    private:
        T _value;

    public:
        basic_header(header::code id, const std::string& name);
        basic_header(header::code id, const std::string& name, const T& value);

        void add_linear(const linear_type& linear_data) override;
        linear_type value_linear() override;
        header& operator=(const header&) override;

        void add(const T& value);
        const T& value() const;
    };

    // multi value header
    template<class T>
    class basic_header<std::vector<T>> : public header
    {
    private:
        std::vector<T> _value;

    public:
        basic_header(header::code id, const std::string& name);
        basic_header(header::code id, const std::string& name, const T& value);
        virtual ~basic_header() {}

        void add_linear(const linear_type& linear_data) override;
        linear_type value_linear() override;
        header& operator=(const header&) override;

        void add(const T& value);
        const T& value(size_t index = 0) const;
        size_t size() const;
    };



    namespace headers
    {
        namespace detail { template<int T> struct initializer {}; }

        // req_id
        class NXS_SHARED req_id : public basic_header<size_t>
        {
        public:
            constexpr static header::code id() { return header::req_id; }
            constexpr static const char* name() { return "req_id"; }
            static size_t id_;

            req_id() : basic_header(id() , name(), id_++) {}
            req_id(size_t value) : basic_header(id() , name(), value) {}

            void preprocess(network::protocol&) override;
        };
        namespace detail { template<> struct initializer<header::req_id> { using type = headers::req_id; }; }

        // data_size
        class NXS_SHARED data_size : public basic_header<std::vector<size_t>>
        {
        private:
            size_t _data_index;
            size_t _data_offset;
        public:
            constexpr static header::code id() { return header::data_size; }
            constexpr static const char* name() { return "data_size"; }

            data_size() : basic_header(id() , name()) {}
            data_size(size_t value) : basic_header(id() , name(), value) { }

            void preprocess(network::protocol&) override;
            void process(network::protocol&) override;
        };
        namespace detail { template<> struct initializer<header::data_size> { using type = headers::data_size; }; }

        // data_target
        class NXS_SHARED data_target : public basic_header<std::vector<size_t>>
        {
        public:
            constexpr static header::code id() { return header::data_target; }
            constexpr static const char* name() { return "data_target"; }
            enum valuec { hdd = 8, memory = 9 };

            data_target() : basic_header(id() , name()) {}
            data_target(valuec value) : basic_header(id() , name(), value) {}
        };
        namespace detail { template<> struct initializer<header::data_target> { using type = headers::data_target; }; }

        // user_name
        class NXS_SHARED user_name : public basic_header<std::string>
        {
        public:
            constexpr static header::code id() { return header::user_name; }
            constexpr static const char* name() { return "user_name"; }

            user_name() : basic_header(id() , name()) {}
            user_name(const std::string& value) : basic_header(id() , name(), value) {}

            void preprocess(network::protocol&) override;
        };
        namespace detail { template<> struct initializer<header::user_name> { using type = headers::user_name; }; }

    } // headers
} // nxs

#include "header.tpp"

#endif // NETWORK_HEADER_H_NXS
