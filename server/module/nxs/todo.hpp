// update data.hpp with double dispatch
// update class data, virtual functins, remove size
// check if network_download_path exist
// MAKE NETWORK::DATA BETTER
// MAKE REQUEST BETTER

// TODO add user id for resource access
//nxs::resource::list(source_id, {2, 5}, {"movie", "serie"})
nxs::resource resource(4, user);
resource.list( {2, 5}, {"movie", "serie"} ) // std::initializer_list of connexion, and types
std::vector<type> resource.type_list();