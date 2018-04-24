namespace nxs{namespace network
{
    template<class Protocol>
    std::unique_ptr<protocol> protocol::create(network::connexion& cnx)
    {
        return std::make_unique<Protocol>(cnx);
    }
}} // nxs::network
