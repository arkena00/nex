#ifndef NXI_PAGE_SYSTEM_H_NXI
#define NXI_PAGE_SYSTEM_H_NXI

#include <ui/window.hpp>

#include <QObject>
#include <QDebug>
#include <QAbstractItemModel>

namespace nxi
{


    enum class page_type { web, explorer, node };

    class page
    {
    public:
        unsigned int id() const { return id_; }
        const QString& name() const { return name_; }

    protected:
        page(unsigned int id, const QString& name)
            : id_{ id }
            , name_{ name }
        {}

    private:
        unsigned int id_;
        QString name_;
    };

    class page_node : public nxi::page
    {
    public:
        page_node(unsigned int id) : nxi::page(id, "new node") {}

        page_node(unsigned int id, const QString& name) : nxi::page(id, name) {}

    private:
    };

    class web_page : public nxi::page
    {
    public:
        web_page(unsigned int id) : nxi::page(id, "web_page"), url_{ "http://www.google.fr" } {}

        const QString& url() const { return url_; }

    private:
        QString url_;
    };

    struct explorer_page : nxi::page
    {
        std::string path;

        explorer_page(unsigned int id) : nxi::page(id, "explorer_page") {}
    };


    // page : ID | page_name | page_type
    // page_connection : source_id | target_id


    class page_system : public QObject
    {
        Q_OBJECT
    public:
        void load();

        void load(nxi::web_page page);

        nxi::page& get(int id);

        /*std::vector<nxi::page&> list(unsigned int id)
        {

        }*/

        //void add(nxi::page page);

        template<class Page>
        void add(unsigned int source_id = 0)
        {
            auto id = static_cast<unsigned int>(pages_.size());

            auto p = std::make_unique<Page>(id);

            pages_.emplace(id, std::move(p));
            page_connections_.emplace(source_id, id);

            emit event_add(static_cast<Page&>(get(id)), source_id);
            //change(page.id);
        }

        void change(unsigned int id);

        template<class Page>
        void change(unsigned int id)
        {
            emit event_change(static_cast<Page&>(get(id)));
            emit event_change(get(id));
        }

        void update(int id);

        signals:
        //void event_add(nxi::page_node);

        void event_add(nxi::page&);

        void event_add(nxi::page_node&, unsigned int source_id);
        void event_add(nxi::web_page&, unsigned int source_id);
        void event_add(nxi::explorer_page&, unsigned int source_id);

        void event_change(nxi::page&);
        //void event_change(nxi::web_page&);

        void event_load(nxi::web_page&);

        void event_update(const nxi::page&);
        void event_update(const nxi::web_page&);

    private:
        nxi::page* current_page_;
        std::vector<nxi::page*> visible_pages_;

        std::map<int, std::unique_ptr<nxi::page>> pages_;
        std::unordered_map<int, int> page_connections_;
    };
} // nxi

#endif // NXI_PAGE_SYSTEM_H_NXI
/* add
 * load
 * update
 * focus
 *
 *
 */