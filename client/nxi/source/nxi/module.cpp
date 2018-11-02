#include <nxi/module.hpp>

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

            auto background = obj["background"].toObject();
            auto scripts = background["scripts"].toArray();

            qDebug() << "________load " << obj["name"].toString();
            qDebug() << "________" << scripts.size();

            for (auto s : scripts)
            {
                nxi_log << "load web_module script " << s.toString().toStdString();
            }

            auto str = obj["description"].toString();
        }
    }
} // nxi