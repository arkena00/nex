#ifndef NETWORK_CONNEXION_MANAGER_H_NXS
#define NETWORK_CONNEXION_MANAGER_H_NXS

#include <boost/asio.hpp>

namespace nxs{namespace network
{
    template<class Connexion>
    class connexion_manager
    {
    private:
        std::map<int, std::unique_ptr<Connexion>> _connexion_list;

        boost::asio::io_service m_ios;
        boost::asio::io_service::work m_work;

    public:
        connexion_manager();
        connexion_manager(const connexion_manager&) = delete;
        virtual ~connexion_manager() = default;

        void store(std::unique_ptr<Connexion>);
        virtual void run();
        virtual void stop();

        boost::asio::io_service& ios();

        Connexion& connexion(size_t id) const;
        void connexion_delete(size_t id);
        bool connexion_exist(size_t id) const;
        size_t connexion_count() const;
    };
}} // nxs::network

#include "manager.tcc"

#endif // NETWORK_CONNEXION_MANAGER_H_NXS
