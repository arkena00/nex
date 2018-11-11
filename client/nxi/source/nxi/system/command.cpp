#include <nxi/system/command.hpp>

#include <nxi/core.hpp>
#include <nxi/system/page.hpp>

#include <QUrl>
#include <nxi/system/command.hpp>
#include <nxi/system/module.hpp>
#include <nxi/error.hpp>
#include <include/nxi/module/web.hpp>
#include <include/nxi/system/command.hpp>


namespace nxi
{
    command_system::command_system(nxi::core& nxi_core) :
        nxi_core_{ nxi_core }
    {}

    void command_system::load()
    {
        // add nxi commands
        nxi::command quit("nxi", "quit", std::bind(&nxi::core::quit, &nxi_core_), ":/button/quit");
        add(std::move(quit));

        nxi::command zeta("nxi", "zeta", std::bind(&nxi::core::quit, &nxi_core_), ":/image/nex");
        add(std::move(zeta));


        // load module commands
        /*
        for (auto& module : nxi_core_.module_system().get())
        {
            if (module->type() == module_type::web)
            {
                auto web_module = static_cast<const nxi::web_module&>(*module);
                nxi::command cmd(module->name(), web_module.browser_action().default_title, std::bind(&nxi::core::quit, &nxi_core_), "module/webextension/test/" + web_module.browser_action().default_icon);
                add(std::move(cmd));
            }
        }*/

/*        nxi::module_load
        if (is_module_command) nxi.command_system()get(cmd).exec()
        else ui.command_system().get(cmd).exec()

        button { "nxi:quit" }*/
    }

    const std::vector<std::unique_ptr<nxi::command>>& command_system::get()
    {
        return commands_;
    }

    const nxi::command& command_system::get(const QString& action_name, const QString& module_name) const
    {
        if (!command_indexes_.count(action_name)) nxi_error << "command not found : " << action_name.toStdString();
        return *commands_[command_indexes_[action_name]];
    }

    void command_system::add(nxi::command command)
    {
        size_t index = commands_.size();
        command_indexes_.insert(command.action_name(), index);
        commands_.push_back(std::make_unique<nxi::command>(std::move(command)));

        emit event_add(*commands_[index]);
    }

    void command_system::exec(const QString& command, command_context context)
    {
        QUrl url{ command };
        qDebug() << "scheme : " << url.scheme() << "__" << url.path();

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

    std::vector<nxi::command> command_system::search(const QString& search_string)
    {
        std::vector<nxi::command> commands;

        for (const auto& command : commands_)
        {
            qDebug() << "search " << search_string << " match : " << command->name();
            if (command->name().contains(search_string)) commands.push_back(*command);
        }

        return commands;
    }
} // nxi

/* /aze/zer // explorer path
 * proto://host // net path
 * search_context/ search expression // search in widgets
 */