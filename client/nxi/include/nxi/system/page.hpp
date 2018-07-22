#ifndef NXI_PAGE_SYSTEM_H_NXI
#define NXI_PAGE_SYSTEM_H_NXI

#include <ui/window.hpp>

#include <QObject>

namespace nxi
{
    class page_system : public QObject
    {
        Q_OBJECT
    public:
        void add(ui::interface* ui)
        {
            emit event_add(ui);
        }

        void change(ui::interface* interface, int index)
        {
            emit event_change(interface, index);
        }

        signals:
        void event_add(ui::interface* source);
        void event_change(ui::interface* source, int index);

        //QHash<ui::interface*, int> page_index_;
    };
} // nxi

#endif // NXI_PAGE_SYSTEM_H_NXI