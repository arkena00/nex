#include <nxi/system/command.hpp>

#include <nxi/core.hpp>
#include <nxi/system/page.hpp>

namespace nxi
{
    command_system::command_system(nxi::core& nxi_core) :
        m_nxi_core{ nxi_core }
    {}

    void command_system::load() {}

    void command_system::exec(const QString& command)
    {

        nxi::web_page page;
        page.url = command.toStdString();
        m_nxi_core.page_system().load(std::move(page));
    }
} // nxi