#include <nxw/shortcut.hpp>

#include <nxw/vbox_layout.hpp>

namespace nxw
{
    shortcut_view::shortcut_view(shortcut* shortcut) :
        QWidget(shortcut),
        shortcut_{ shortcut }
    {
        view_ = new QListWidget(this);
        view_->setFixedWidth(400);

        label_ = new QLabel(this);
        label_->setText("SHORTCUT");

        auto main_layout = new nxw::vbox_layout(this);
        main_layout->addWidget(label_);
        main_layout->addWidget(view_);

        setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog | Qt::Tool);
        setLayout(main_layout);
    }

    void shortcut_view::keyPressEvent(QKeyEvent* event)
    {
        shortcut_->process(event);
    }

    void shortcut_view::keyReleaseEvent(QKeyEvent* event)
    {
        shortcut_->process(event);
    }

    void shortcut_view::showEvent(QShowEvent* event)
    {
        QWidget::showEvent(event);
        auto win = shortcut_->window();
        auto x = win->width() / 2 - view_->width() / 2 + win->pos().x();
        auto y = win->height() / 2 - view_->height() / 2 + win->pos().y();

        move(x, y);
    }

    void shortcut_view::add(shortcut_item item)
    {
        view_->addItem(to_string(item) + " | " + item.name);
    }

    void shortcut_view::event_change(std::vector<shortcut_item> shortcuts)
    {
        QString name;
        view_->clear();

        for (auto shortcut : shortcuts)
        {
            add(shortcut);
        }

        label_->setText(name);
    }

    QString shortcut_view::to_string(Qt::Key key)
    {
        QString name;
        switch(key)
        {
            case Qt::Key_Control: name += "CTRL"; break;
            case Qt::Key_Shift: name += "SHIFT"; break;
            case Qt::Key_Alt: name += "ALT"; break;
            default:
                name += QKeySequence(key).toString();
        }
        return name;
    }

    QString shortcut_view::to_string(shortcut_item item)
    {
        QString sc_str;
        for (auto k : item.combo_keys)
        {
            sc_str += "+" + to_string(k);
        }
        for (auto k : item.sequence_keys)
        {
            sc_str += ">" + to_string(k);
        }
        return sc_str;
    }
} // nxw