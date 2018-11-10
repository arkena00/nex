#ifndef NXI_MODULE_WEB_H_NXI
#define NXI_MODULE_WEB_H_NXI

#include <nxi/database.hpp>
#include <nxi/module.hpp>

namespace nxi
{
    class core;

    class web_module : public module
    {
        struct background
        {
            std::vector<QString> scripts;
        };

        struct browser_action_data
        {
            bool browser_style = false;
            QString default_area;
            QString default_icon;
            QString default_popup;
            QString default_title;
        };

        struct commands
        {
            // std::map<QString, nxi::shortcut> shortcuts_;
        };

        struct content_script
        {
            std::vector<QString> matches;
            std::vector<QString> js;
        };

    public:
        web_module(nxi::core&, const QString& name);

        void on_load() override;

        auto& browser_action() const { return browser_action_; }

    private:
        nxi::core& nxi_core_;

        // applications
        QString author_;
        background background_;
        browser_action_data browser_action_;
        // chrome_settings_overrides
        // chrome_url_overrides
        commands commands_;
        std::vector<content_script> content_scripts_;
        // content_security_policy
        // default_locale
        QString description_;
        // developer
        // devtools_page
        QString homepage_url_;
        // icons
        // incognito
        int manifest_version_;
        QString name_;
        // omnibox
        // optional_permissions
        // option_ui
        // page_action
        // permissions
        // protocol_handlers
        QString short_name;
        // sidebar_action
        // theme
        QString version_;
        QString version_name_;
        // web_accessible_resources
    };
} // nxi

#endif // NXI_MODULE_WEB_H_NXI