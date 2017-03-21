#ifndef NETWORK_CONNEXION_MANAGER_H_NXS
#define NETWORK_CONNEXION_MANAGER_H_NXS

#include <boost/asio.hpp>

namespace nxs{namespace network
{
    template<class Connexion>
    class NXS_SHARED connexion_manager
    {
    private:
        std::map<int, std::unique_ptr<Connexion>> _connexion_list;

        boost::asio::io_service _ios;

    public:
        connexion_manager() = default;
        connexion_manager(const connexion_manager&) = delete;

        void store(std::unique_ptr<Connexion>);
        virtual void run();

        boost::asio::io_service& ios();

        Connexion& connexion(size_t id) const;
        void connexion_close(size_t id);
        bool connexion_exist(size_t id) const;
        size_t connexion_count() const;
    };
}} // nxs::network

#include "manager.tpp"

#endif // NETWORK_CONNEXION_MANAGER_H_NXS
