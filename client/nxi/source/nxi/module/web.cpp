#include <nxi/module/web.hpp>

#include <nxi/log.hpp>

#include <QString>
#include <QFile>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include <QDebug>
#include <nxi/core.hpp>
#include <nxi/command.hpp>
#include <nxi/system/command.hpp>
#include <nxi/module/web.hpp>


namespace nxi
{

    web_module::web_module(nxi::core& nxi_core, const QString& name)
        : module(name, module_type::web)
        , nxi_core_{ nxi_core }
    {
        QFile module_file("./module/webextension/"+ name +"/manifest.json");

        if (!module_file.open(QFile::ReadOnly)) qDebug() << "read error : " << module_file.fileName();
        else
        {
            QJsonDocument doc = QJsonDocument::fromJson(module_file.readAll());
            QJsonObject obj = doc.object();
            module_file.close();

            // manifest keys
            name_ = obj["name"].toString();
            description_ = obj["description"].toString();

            auto background = obj["background"].toObject();
            auto scripts = background["scripts"].toArray();

            for (auto s : scripts)
            {
                nxi_log << "load web_module script " << s.toString().toStdString();
            }

            // content_scripts
            if (obj["content_scripts"].isArray())
            {
                for (auto json_content_script : obj["content_scripts"].toArray())
                {
                    web_module::content_script content_script;

                    for (auto json_match : json_content_script.toObject()["matches"].toArray())
                        content_script.matches.push_back(json_match.toString());

                    for (auto json_js : json_content_script.toObject()["js"].toArray())
                        content_script.js.push_back(json_js.toString());

                    content_scripts_.push_back(std::move(content_script));
                }
            }

            // browser_action
            if (obj["browser_action"].isObject())
            {
                browser_action_.default_title = obj["browser_action"].toObject()["default_title"].toString();
                browser_action_.default_icon = obj["browser_action"].toObject()["default_icon"].toString();
                browser_action_.default_popup = obj["browser_action"].toObject()["default_popup"].toString();
            }

            for (web_module::content_script cs : content_scripts_)
            {
                for (auto m : cs.matches) qDebug() << "m__" << m;
                for (auto j : cs.js) qDebug() << "j__" << j;
            }
        }
    }

    void web_module::on_load()
    {
        // add module commands
        auto f = [this]()
        {
            if (browser_action_.default_popup.isEmpty()) nxi_core_.page_system().add<nxi::web_page>(0);
            else nxi_core_.command_system().get("quit").exec();
        };
        nxi::command command{ "wm-" + name(), "main", f, "./module/webextension/"+ name() +"/" + browser_action_.default_icon };
        nxi_core_.command_system().add(std::move(command));
    }
} // nxi