#include <nxi/system/command.hpp>

#include <nxi/core.hpp>
#include <nxi/system/page.hpp>

#include <QUrl>

namespace nxi
{
    command_system::command_system(nxi::core& nxi_core) :
        nxi_core_{ nxi_core }
    {}

    void command_system::load() {}

    void command_system::exec(const QString& command, command_context context)
    {
        QUrl url{ command };
        qDebug() << "scheme : " << url.scheme();

        switch (context)
        {
            case command_context::deduced:


                break;
            case command_context::web:
            {
                qDebug() << "exec web";
                nxi::web_page page;
                page.url = command.toStdString();
                nxi_core_.page_system().load(std::move(page));
            }
                break;
            case command_context::explorer:
                break;
        }
    }
} // nxi