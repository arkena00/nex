#ifndef NEX_H_NXS
#define NEX_H_NXS

namespace nxs
{
    class request;
    class user;

    namespace network { class protocol; }

    class nex
    {
    public:
        virtual ~nex() {}
        virtual nxs::user& user() = 0;
        virtual request& input() = 0;
        virtual request& output() = 0;
        virtual bool transfer_complete() const = 0;
        virtual bool process_complete() const = 0;

        network::protocol& protocol();
    };
} // nxs

#endif // NEX_H_NXS
