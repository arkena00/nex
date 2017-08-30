#ifndef UI_TAB_H_NXI
#define UI_TAB_H_NXI

#include <nxs/network/connexion/output.hpp>
#include <nxs/network/url.hpp>

#include <QWidget>
#include <QString>

class QLineEdit;
class QStackedWidget;

namespace ui
{
    class main;
    class tabbar;
    class tree;

    class tab : public QWidget
    {
        Q_OBJECT
    private:
        ui::main* _main;
        size_t _connexion_id;
        size_t _id;

        QString _name;
        nxs::network::url _url;

        QLineEdit* _address_bar;
        ui::tree* _tree;
        QStackedWidget* _engine_stack;

    public:
        tab(ui::main* main_window, size_t index);
        ~tab();

        void load(const nxs::network::url&);
        void address_load();

        void on_connexion_connect();
        void on_transfer_progress(unsigned int);
        void on_connexion_close();

        size_t id() const;
        ui::tabbar& tabbar() const;
        nxs::network::output_connexion& connexion();

        void title_set(const std::string&);
        void icon_set(const QIcon&);


    signals:
        void engine_load(const QString&);
        void event_connexion_connect();
        void event_connexion_close();

        void event_transfer_complete();
        void event_transfer_progress(int);
    };

} // ui

#endif // UI_TAB_H_NXI
