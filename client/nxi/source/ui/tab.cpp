#include <ui/tab.hpp>
#include <ui/tabbar.hpp>
#include <ui/main.hpp>
#include <ui/tree.hpp>
#include <ui/tree/item.hpp>
#include <ui/render/engine.hpp>

#include <nxs/network/request.hpp>
#include <nxs/network/protocol.hpp>
#include <nxs/network/connexion/output.hpp>
#include <nxs/network/buffer.hpp>

#include <QHBoxLayout>
#include <QSplitter>
#include <QLineEdit>
#include <QTabBar>
#include <QStackedWidget>
#include <QDebug>
#include <include/ui/render/web.hpp>
#include <QMetaMethod>

namespace ui
{
    tab::tab(ui::main* main_window, size_t index) :
        _main(main_window),
        _id((size_t)reinterpret_cast<void*>(this))
    {
        // link tab widget to tab
        tabbar().setTabData(index, _id);

        qRegisterMetaType<nxs::network::error_code>("error_code");
        // create new connexion
        using output_connexion = nxs::network::output_connexion;
        output_connexion& cnx = _main->client().connexion_add();
        _connexion_id = cnx.id();
        // bind connexion events
        cnx.on_connect([this]() { emit event_connexion_connect(); });
        cnx.on_close([this](const nxs::network::error_code& status) { emit event_connexion_close(); });

        /*
        cnx.on_read([this](output_connexion& out)
                    {
                        emit engine_load(out.protocol().input().data(0).get().c_str());
                    }
        );*/

        QObject::connect(this, &tab::event_connexion_connect, this, &tab::on_connexion_connect, Qt::QueuedConnection);
        QObject::connect(this, &tab::event_transfer_progress, this, &tab::on_transfer_progress, Qt::QueuedConnection);
        QObject::connect(this, &tab::event_connexion_close, this, &tab::on_connexion_close, Qt::QueuedConnection);


        // main layout
        QVBoxLayout *main_layout      = new QVBoxLayout(this);
        QHBoxLayout *top_layout       = new QHBoxLayout;
        QHBoxLayout *interface_layout = new QHBoxLayout;
        QHBoxLayout *middle_layout    = new QHBoxLayout;
        QVBoxLayout *left_layout      = new QVBoxLayout;
        QVBoxLayout *right_layout     = new QVBoxLayout;
        QHBoxLayout *bot_layout       = new QHBoxLayout;
        // splitter
        QSplitter   *splitter         = new QSplitter(this);
        QWidget     *left_side        = new QWidget(this);
        QWidget     *right_side       = new QWidget(this);

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

        auto engine = new render::web(this);
        engine->load("started");
        _engine_stack->addWidget(engine->widget());
        QObject::connect(this, &tab::engine_load, engine, &render::engine::load);
        engine->setUrl(QUrl("http://www.google.fr"));

        // default value
        _address_bar->setText(_url.str().c_str());
    }

    tab::~tab()
    {
        _main->client().connexion_delete(_connexion_id);
    }

    void tab::load(const nxs::network::url& url)
    {

    }

    void tab::address_load()
    {
        try
        {
            const std::string& address_text = _address_bar->text().toStdString();
            _url = nxs::network::url(address_text);

            // connexion alive, send command
            if (connexion().is_alive())
            {
                connexion().protocol().send(_url.command(), [this](nxs::nex& nex)
                {
                      engine_load(nex.input().data().get().c_str());
                });
            }
            else
            {
                title_set("connecting...");
                connexion().connect(_url.host(), _url.port());
            }

            // loading
            icon_set(QIcon(":/image/connexion_status_idle"));
        } catch (const std::exception& e)
        {
            emit engine_load(e.what());
        }
    }

    void tab::on_connexion_connect()
    {
        engine_load("on_connexion_connect");
        icon_set(QIcon(":/image/connexion_status_1"));
        title_set(std::to_string(_id));
        auto item = _tree->item_add(_url.host().c_str(), QIcon(":/image/nex"));
        item->node(true);
    }

    void tab::on_transfer_progress(unsigned int n)
    {

    }


    void tab::on_connexion_close()
    {
        icon_set(QIcon(":/image/connexion_status_0"));
    }

    size_t tab::id() const
    {
        return _id;
    }

    ui::tabbar& tab::tabbar() const
    {
        return _main->tabbar();
    }

    nxs::network::output_connexion &tab::connexion()
    {
        return _main->client().connexion(_connexion_id);
    }

    void tab::icon_set(const QIcon &icon)
    {
        tabbar().setTabIcon(tabbar().index(this), icon);
    }

    void tab::title_set(const std::string &title)
    {
        tabbar().setTabText(tabbar().index(this), title.c_str());
    }
} // ui
