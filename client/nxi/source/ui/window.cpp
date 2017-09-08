#include "ui/window.hpp"
#include "ui/main.hpp"
#include "ui/tab.hpp"
#include "ui/tabbar.hpp"

#include <nxs/network/connexion/output.hpp>

#include <QIcon>
#include <QDesktopWidget>
#include <QVBoxLayout>

namespace ui
{
    window::window(nxi::core& nxc) : nxc_(nxc)
    {
        QIcon icon(":image/nex");
        setWindowIcon(icon);
        //setWindowFlags( Qt::CustomizeWindowHint );

        // main window
        QDesktopWidget screen;
        QRect screen_size = screen.availableGeometry(screen.primaryScreen());
        size_t width = screen_size.width() * 0.8;
        size_t height = screen_size.height() * 0.7;
        size_t x = (screen_size.width() - width) / 2;
        size_t y = (screen_size.height() - height) / 2;
        // center window
        resize(width, height);
        move(x, y);
        setWindowTitle("nxi");

        main_ = new ui::main(this);

        QVBoxLayout* main_layout = new QVBoxLayout(this);
        main_layout->addWidget(main_);
        main_layout->setContentsMargins(0, 0, 0, 0);

        // systray
        systray_ = new QSystemTrayIcon(this);
        systray_->setIcon(QIcon(":/image/nex"));
        systray_->show();

    }

    window::~window()
    {
    }

    nxi::core& window::nxc()
    {
        return nxc_;
    }
} // ui
