#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QDebug>

#include <nxs/database.hpp>
#include <nxs/resource/type.hpp>

#include <boost/filesystem.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    std::string output;

    QLabel l(&w);

    sqlite3* _db;

    try {
    boost::filesystem::create_directory("./database");


    ndb::engine<>::model_add(db::nex);
    ndb::engine<>::connect("nxs");

    for (nxs::type& t : nxs::type::get())
    {
        output += "<br />" + std::to_string(t.id()) + " " + t.author() + " " + t.name();
    }

    l.setText(output.c_str());

    w.show();

    } catch(const std::exception& e) { qDebug() << e.what(); }

    return a.exec();
}
