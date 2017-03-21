#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QtConcurrent/QtConcurrentRun>
#include <functional>

#include <nxs/database.hpp>
#include <nxs/resource.hpp>
#include <nxs/resource/type.hpp>
#include <nxs/network/header.hpp>
#include <nxs/network/server.hpp>
#include <nxs/command.hpp>

#include <boost/filesystem.hpp>

QLabel* loglabel;

void ui_log(const std::string& msg)
{
    QString z = loglabel->text();
    z+= msg.c_str();
    loglabel->setText(z);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;
    loglabel = new QLabel(&w);
    loglabel->setFixedSize(800, 400);
    std::string output;

    std::function<void(const std::string&)> fn;

    nxs::log::redirect_output(ui_log);

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

    w.show();

    void (*ptr)(short);
    ptr = &nxs::network::server::start;

    QtConcurrent::run(ptr, 5050);

    } catch(const std::exception& e) { qDebug() << e.what(); }

    return a.exec();
}
