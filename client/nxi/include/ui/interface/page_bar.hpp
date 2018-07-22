#ifndef UI_PAGE_BAR_H_NXI
#define UI_PAGE_BAR_H_NXI

#include <QStackedWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QtGui/qpainter.h>

#include <QTabBar>

#include <ui/window.hpp>
#include <ui/interface.hpp>

#include <nxi/system/page.hpp>

#include <ui/core.hpp>

#include <QPushButton>

namespace ui
{
    namespace interfaces
    {
        class page_bar : public ui::interface
        {
        public:

            page_bar(ui::core& ui_core, ui::interface* ui) :
            m_ui_core{ ui_core }
            , m_interface{ ui }
            {
                tabbar_ = new QTabBar(this);

                tabbar_->addTab("test");
                tabbar_->addTab("test2");

                auto btn = new QPushButton(this);
                connect(btn, &QPushButton::clicked, this, [this]()
                {
                    m_ui_core.nxi_core().page_system().add(m_interface);
                });

                connect(&m_ui_core.nxi_core().page_system(), &nxi::page_system::event_add, this, [this]()
                {
                    tabbar_->addTab("page_added");
                });

                connect(tabbar_, &QTabBar::tabBarClicked, this, [this](int index)
                {
                    m_ui_core.nxi_core().page_system().change(this, index);
                });
            }

            QTabBar* tabbar_;
            ui::core& m_ui_core;
            ui::interface* m_interface;
        };
    }
} // ui

#endif