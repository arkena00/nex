#include <nxi/tab_system.hpp>

namespace nxi
{
    void tab_system::on_add(QWidget* source)
    {
        nxi::tab new_tab;

        tabs_.push_back(new_tab);

        emit event_add(source, new_tab);
    }

    void tab_system::on_change(QWidget* source, int index)
    {
        //tabs_[index]
        emit event_change(source, index);
    }
} // nxi
