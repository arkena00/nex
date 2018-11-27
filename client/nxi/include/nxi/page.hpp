#ifndef NXI_PAGE_H_NXI
#define NXI_PAGE_H_NXI

#include <nxi/page/id.hpp>
#include <nxi/type.hpp>

#include <QObject>
#include <QString>

namespace nxi
{
    class page_system;

    class page : public QObject
    {
        Q_OBJECT
    public:
        nxi::page_id id() const;
        const QString& name() const;

        virtual void focus() = 0;
        virtual void load();

        void name_update(const QString& name);

    protected:
        page(page_system& ps, nxi::page_id id, const QString& name);

        nxi::page_system& page_system_;

    private:
        nxi::page_id id_;
        QString name_;

    signals:
        void event_update_name(const QString&);
        void event_load();
    };
} // nxi

#endif // NXI_PAGE_H_NXI