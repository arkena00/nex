#include <ui/tab.hpp>
#include <ui/tree.hpp>
#include <ui/main.hpp>


#include <nxw/hbox_layout.hpp>
#include <nxw/tabbar.hpp>

#include <QPushButton>
#include <ui/render/engine.hpp>
#include <ui/render/web_page.hpp>

#include <nxw/vbox_layout.hpp>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabBar>
#include <QWebEnginePage>

namespace ui
{
    tab::tab(ui::main* ui_main) :
        QWidget(ui_main),
        main_{ ui_main }
    {
        // tree
        tree_ = new ui::tree(this);

        auto main_layout = new nxw::hbox_layout;
        //main_layout->addWidget(tree_);


        page_ = new render::web_page(this);
        page_->load("http://www.google.fr");
        connect(static_cast<render::web_page*>(page_)->widget(), &QWebEnginePage::loadProgress, [this](int progress) { main_->tabbar_->setTabText(0, QString::number(progress)); });

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

        main_layout->addWidget(tree_);
        main_layout->addLayout(engine_layout_);

        main_->tabwidget_->layout_.insert(main_->tabwidget_->stack()->count(), engine_layout_);
        qDebug() << "add  " << engine_layout_ << " at " << main_->tabwidget_->stack()->count();

        setLayout(main_layout);

    }
/*
    tab::~tab()
    {
        //tabwidget_->main().client().connexion_delete(connexion_id_);
    }*/

} // ui
