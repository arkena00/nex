#ifndef CORE_H_NXI
#define CORE_H_NXI

#include <nxs/network/client.hpp>
#include <nxi/tabsystem.hpp>

#include <QWidget>
#include <QDebug>

namespace nxi
{
    class core
    {
    public:
        core();
        ~core();
        core(const core&) = delete;
        void operator=(const core&) = delete;

        nxs::network::client& client();
        nxi::tabsystem& tabsystem();


    private:
        nxs::network::client client_;
        std::thread client_thread_;

        nxi::tabsystem tabsystem_;
    };
} // nxi

#endif // CORE_H_NXI