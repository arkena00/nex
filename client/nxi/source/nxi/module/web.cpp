#include <nxi/module/web.hpp>

#include <nxi/log.hpp>

#include <QString>
#include <QFile>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include <QDebug>

namespace nxi
{

    web_module::web_module(const QString& name)
    {
        QFile module_file("./module/webextension/"+ name +"/manifest.json");

        if (!module_file.open(QFile::ReadOnly)) qDebug() << "read error";
        else
        {
            QJsonDocument doc = QJsonDocument::fromJson(module_file.readAll());
            QJsonObject obj = doc.object();
            module_file.close();

            // manifest keys
            name_ = obj["name"].toString();
            auto background = obj["background"].toObject();
            auto scripts = background["scripts"].toArray();

            for (auto s : scripts)
            {
                nxi_log << "load web_module script " << s.toString().toStdString();
            }

            auto str = obj["description"].toString();

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
                qDebug() << browser_action_.default_title;
            }

            for (web_module::content_script cs : content_scripts_)
            {
                for (auto m : cs.matches) qDebug() << "m__" << m;
                for (auto j : cs.js) qDebug() << "j__" << j;
            }
        }
    }
} // nxi