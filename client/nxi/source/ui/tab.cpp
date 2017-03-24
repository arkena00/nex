#include "ui/tab.hpp"
#include "ui/main.hpp"
#include "ui/tree.hpp"
#include <ui/tree/item.hpp>

#include <nxs/network/request.hpp>
#include <nxs/network/protocol.hpp>
#include <nxs/network/connexion/output.hpp>
#include <nxs/network/buffer.hpp>

#include <QTabBar>
#include <QHBoxLayout>
#include <QSplitter>
#include <QLineEdit>
#include <QTabBar>
#include <QStackedWidget>
#include <QDebug>
#include <thread>


namespace ui
{
    tab::tab(ui::main* main_window, size_t tab_index) :
        _main(main_window),
        _index(tab_index)
    {
        // create new connexion
        nxs::network::output_connexion& cnx = _main->client().connexion_add();
        _connexion_id = cnx.id();
        // bind connexion events
        cnx.on_connect(std::bind(&tab::on_connect, this));
        cnx.on_read(std::bind(&tab::on_read, this, cnx.buffer()));
        cnx.on_error(std::bind(&tab::on_error, this));

        // main layout
        QVBoxLayout* main_layout = new QVBoxLayout(this);
        QHBoxLayout* top_layout = new QHBoxLayout;
        QHBoxLayout* interface_layout = new QHBoxLayout;
        QHBoxLayout* middle_layout = new QHBoxLayout;
        QVBoxLayout* left_layout = new QVBoxLayout;
        QVBoxLayout* right_layout = new QVBoxLayout;
        QHBoxLayout* bot_layout = new QHBoxLayout;
        // splitter
        QSplitter* splitter = new QSplitter(this);
        QWidget* left_side = new QWidget(this);
        QWidget* right_side = new QWidget(this);

        // layouts
        main_layout->addLayout(top_layout);
        main_layout->addLayout(interface_layout);
        main_layout->addLayout(middle_layout);
        main_layout->addLayout(bot_layout);
        main_layout->setMargin(0);

        // splitter
        left_side->setLayout(left_layout);
        left_side->setMinimumWidth(150);
        left_layout->setMargin(0);
        right_layout->setMargin(0);
        right_side->setLayout(right_layout);
        splitter->addWidget(left_side);
        splitter->setStretchFactor(0, 0);
        splitter->addWidget(right_side);
        splitter->setStretchFactor(1, 1);
        middle_layout->addWidget(splitter);

        // address
        _address_bar = new QLineEdit(this);
        _address_bar->setObjectName("address");
        top_layout->addWidget(_address_bar);
        QObject::connect(_address_bar, &QLineEdit::returnPressed, this, &tab::address_load);

        // tree
        _tree = new ui::tree(this);
        _tree->setObjectName("resource_tree");
        _tree->setHeaderHidden(1);
        _tree->setStyleSheet("border: none;");

        left_layout->addWidget(_tree);

        // render engine
        _engine_stack = new QStackedWidget(this);
        right_layout->addWidget(_engine_stack);

        //auto engine = new render::nazara;
        //engine->load("started");
        //_engine_stack->addWidget(engine);

        // default value
        _address_bar->setText(_url.str().c_str());
    }

    tab::~tab()
    {
        _main->client().connexion_close(_connexion_id);
    }

    void tab::load(const nxs::network::url& url)
    {

    }

    void tab::address_load()
    {
        const std::string& address_text = _address_bar->text().toStdString();
        _url = nxs::network::url(address_text);

        // connexion alive, send command
        if (connexion().is_alive())
        {
            connexion().protocol().send(_url.command());
        }
        else
        {
            title_set("connecting...");
            connexion().connect(_url.host(), _url.port());
        }

        // loading

        icon_set(QIcon(":/image/connexion_status_idle"));
    }

    void tab::on_connect()
    {
        icon_set(QIcon(":/image/connexion_status_1"));
        auto item = _tree->item_add(_url.host().c_str(), QIcon(":/image/nex"));
        item->node(true);
         connexion().protocol().send("nxs::version;", [](nxs::nex& nn){  qDebug() << "CALLBACK_VER"; });
    }

    void tab::on_read(nxs::network::connexion::buffer_type& buf)
    {

        try {
        connexion().protocol().read();

        if (connexion().protocol().transfer_complete())
        {
            //nazara->load(connexion().protocol().input().data(0).get().c_str());
        }
        } catch (const std::exception& e) {  }
    }

    void tab::on_error()
    {
        icon_set(QIcon(":/image/connexion_status_0"));
    }


    nxs::network::output_connexion& tab::connexion() { return _main->client().connexion(_connexion_id); }

    void tab::icon_set(const QIcon& icon) { tabbar().setTabIcon(_index, icon); }
    void tab::title_set(const std::string& title) { tabbar().setTabText(_index, title.c_str()); }

    QTabBar& tab::tabbar() const { return _main->tabbar(); }
} // ui
