#include <nxs/network/connexion.hpp>

using nxs::network::connexion;

connexion::~connexion()
{

}

void connexion::data_send(const std::string& data)
{
    data_send(data.c_str(), data.size());
}

int connexion::id() const { return _id; }
int connexion::iotype() const { return _iotype; }
bool connexion::alive() const { return _alive; }
