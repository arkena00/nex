#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QtConcurrent/QtConcurrentRun>

#include <nxs/database.hpp>
#include <nxs/resource.hpp>
#include <nxs/resource/type.hpp>
#include <nxs/network/header.hpp>
#include <nxs/network/server.hpp>
#include <nxs/command.hpp>

#include <boost/filesystem.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;
    QLabel l(&w);
    std::string output;

    try {
    boost::filesystem::create_directory("/storage/extSdCard/nex/");

    ndb::engine<>::path_set("/storage/extSdCard/nex/");
    ndb::engine<>::model_add(db::nex);
    ndb::engine<>::connect("nxs");

    nxs::header::init();
    nxs::command::load();

    /*
    nxs::resource::add("John");
    nxs::resource::add("X-men");
    nxs::resource::add("Battlestar");


    nxs::type::add("movie");
    nxs::type::add("serie");
    nxs::type::add("contact");
    nxs::type::add("photo");
    */

    for (nxs::type& t : nxs::type::get())
    {
        output += "<br />" + std::to_string(t.id()) + " " + t.author() + " " + t.name();
    }

    l.setText(output.c_str());

    w.show();

    QtConcurrent::run(&nxs::network::server::start);

    } catch(const std::exception& e) { qDebug() << e.what(); }

    return a.exec();
}
