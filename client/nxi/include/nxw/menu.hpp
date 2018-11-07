#ifndef NXW_MENU_H_NXI
#define NXW_MENU_H_NXI

namespace ui { class core; }

#include <ui/interface.hpp>
#include "vbox_layout.hpp"
#include <QLabel>

namespace nxw
{
    class menu_separator : public QFrame
    {
    Q_OBJECT
    public:
        menu_separator()
        {
            setFrameStyle(QFrame::HLine);
            setFixedHeight(12);
        }
    };

    class menu_item : public QFrame
    {
        Q_OBJECT

        Q_PROPERTY(int height READ height WRITE height_set DESIGNABLE true)

    public:
        menu_item(const QString& str_name, std::function<void()> command = {}, const QString& str_icon = "") :
            command_{ std::move(command) }
        {
            auto layout_ = new nxw::hbox_layout;
            setLayout(layout_);

            auto icon = new QLabel(this);
            if (!str_icon.isEmpty())
            {
                icon->setPixmap(QPixmap(str_icon));
            }
            icon->setFixedWidth(24);

            auto label = new QLabel(this);
            label->setText(str_name);

            layout_->addWidget(icon);
            layout_->addWidget(label);
            layout_->addStretch(1);
        }

        void mouseReleaseEvent(QMouseEvent* event) override
        {
            if (command_) command_();
        }

        int height() const { return height_; }
        void height_set(int h) { height_ = h; setFixedHeight(height_); }

    private:
        int height_;
        std::function<void()> command_;
    };

    class menu : public QFrame
    {
        Q_OBJECT

    public:
        menu(QWidget* parent) :
            QFrame(parent)
            , widget_origin_{ nullptr }
        {
            setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);

            layout_ = new nxw::vbox_layout;
            layout_->setAlignment(layout_, Qt::AlignTop);

            setLayout(layout_);
        }

        template<class Widget, class... Args>
        void add(Args&&... args)
        {
            auto widget = new Widget(std::forward<Args>(args)...);
            layout_->addWidget(widget);
        }

        void add(const nxi::command& command)
        {
            command.action_name();
            add<nxw::menu_item>(command.action_name(), command.function(), ":/button/" + command.action_name());
        }

        void add(QWidget* widget)
        {
            layout_->addWidget(widget);
        }

        void show_at(QWidget* widget)
        {
            widget_origin_ = widget;
        }

        void exec()
        {
            // move menu to widget global position
            auto p = widget_origin_->mapToGlobal(widget_origin_->rect().bottomLeft());
            move(p);
            show();
        }

    private:
        //ui::core& ui_core;
        //std::vector<nxw::menu_item>
        nxw::vbox_layout* layout_;
        QWidget* widget_origin_;

    };
} // nxw

#endif // NXW_MENU_H_NXI