#ifndef UI_TAB_H_NXI
#define UI_TAB_H_NXI

#include <nxs/network/connexion/output.hpp>
#include <nxs/network/url.hpp>

#include <QWidget>

class QLineEdit;
class QWebEnginePage;

namespace ui
{
    class tabwidget;
    class tree;

    namespace render { class engine; class page; }

    class tab : public QWidget
    {
    Q_OBJECT

    private:
        unsigned int id_;
        size_t connexion_id_;
        nxs::network::url url_;

        ui::tabwidget* tabwidget_;
        ui::tree* tree_;
        render::page* page_;

        QLineEdit* address_bar_;

    public:
        tab(ui::tabwidget* main_widget);
        ~tab();

        void address_load();

        size_t id() const;
        nxs::network::output_connexion& connexion();
        render::page& page();

        void title_set(const QString&);
        void icon_set(const QIcon&);

        void on_connexion_connect();
        void on_transfer_progress(unsigned int);
        void on_connexion_close();

    signals:
        void page_load(const QString&);
        void event_connexion_connect();
        void event_connexion_close();

        void event_transfer_complete();
        void event_transfer_progress(int);
    };

} // ui

#endif // UI_TAB_H_NXI
