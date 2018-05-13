#include <ui/tab.hpp>

#include <ui/render/engine.hpp>
#include <ui/render/web_page.hpp>
#include <ui/tabtree.hpp>
#include <ui/tabdata.hpp>
#include <ui/tree.hpp>

#include <nxw/tabwidget.hpp>
#include <nxw/hbox_layout.hpp>
#include <nxw/tabbar.hpp>
#include <nxw/vbox_layout.hpp>

#include <QSplitter>
#include <QWebEnginePage>

namespace ui
{
    tab::tab(nxw::tabwidget* tabwidget) :
        tab_base(tabwidget),
        tabwidget_{ tabwidget }
    {
        // get engine from tabwidget data
        engine_ = static_cast<const ui::tabdata&>(tabwidget_->tabdata()).engine;

        // tree
        tree_ = new ui::tree(this);

        auto main_layout = new nxw::hbox_layout;
        setLayout(main_layout);
        //main_layout->addWidget(tree_);


        engine_page_ = new render::web_page(this);
        engine_page_->load("http://www.google.fr");
        //connect(static_cast<render::web_page*>(page_)->widget(), &QWebEnginePage::loadProgress, [this](int progress) { main_->tabbar_->setTabText(0, QString::number(progress)); });

        // connect web engine events
        connect(static_cast<render::web_page*>(engine_page_)->widget(), &QWebEnginePage::iconChanged, [this](const QIcon& icon)
        {
            tabwidget_->icon_set(this, icon);
        });
        connect(static_cast<render::web_page*>(engine_page_)->widget(), &QWebEnginePage::titleChanged, [this](const QString& title)
        {
            tabwidget_->title_set(this, title);
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
    }


    void tab::on_change()
    {
        engine_->load(engine_page_);
        engine_layout_->addWidget(engine_->widget());
    }

    tab::~tab()
    {
        //main_->engine()->widget()->setParent(main_);
    }
} // ui
