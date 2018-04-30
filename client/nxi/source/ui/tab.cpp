#include <ui/tab.hpp>

#include <ui/tree.hpp>
#include <ui/main.hpp>
#include <ui/render/engine.hpp>
#include <ui/render/web_page.hpp>
#include <ui/tabtree.hpp>

#include <nxw/hbox_layout.hpp>
#include <nxw/tabbar.hpp>
#include <nxw/vbox_layout.hpp>

#include <QSplitter>
#include <QWebEnginePage>

namespace ui
{
    tab::tab(ui::main* ui_main) :
        tab_base(ui_main),
        main_{ ui_main }
    {
        // tree
        tree_ = new ui::tree(this);

        auto main_layout = new nxw::hbox_layout;
        //main_layout->addWidget(tree_);


        page_ = new render::web_page(this);
        page_->load("http://www.google.fr");
        //connect(static_cast<render::web_page*>(page_)->widget(), &QWebEnginePage::loadProgress, [this](int progress) { main_->tabbar_->setTabText(0, QString::number(progress)); });
        connect(static_cast<render::web_page*>(page_)->widget(), &QWebEnginePage::iconChanged, [this](const QIcon& icon)
        {
            auto index = main_->tabwidget_->index(this);
            main_->tabwidget_->icon_set(index, icon);
        });
        connect(static_cast<render::web_page*>(page_)->widget(), &QWebEnginePage::titleChanged, [this](const QString& title)
        {
            auto index = main_->tabwidget_->index(this);
            main_->tabwidget_->title_set(index, title);
        });

        // splitter
        auto splitter = new QSplitter(this);
        auto left_side = new QWidget(this);
        auto right_side = new QWidget(this);
        left_side->setMinimumWidth(150);

/*
        splitter->addWidget(tree_);
        splitter->setStretchFactor(0, 0);
        splitter->addWidget(main_->engine()->widget());
        splitter->setStretchFactor(1, 1);*/

        engine_layout_ = new nxw::hbox_layout;

        //main_layout->addWidget(tree_);
        main_layout->addLayout(engine_layout_);


        setLayout(main_layout);

    }

    void tab::tab_focus(ui::tabdata* tabdata)
    {
        //auto ui_main = static_cast<ui::main*>(widget_main)()
        qDebug() << "SHOW";
        main_->engine()->load(page_);
        engine_layout_->addWidget(main_->engine()->widget());
    }

    tab::~tab()
    {
        main_->engine()->widget()->setParent(main_);
    }


} // ui
