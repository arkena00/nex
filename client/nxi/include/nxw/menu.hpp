#ifndef NXW_MENU_H_NXI
#define NXW_MENU_H_NXI

namespace ui { class core; }

#include <ui/interface.hpp>
#include "vbox_layout.hpp"
#include "hbox_layout.hpp"
#include <QLabel>
#include <QtCore/QEvent>

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
                icon->setPixmap(QPixmap(str_icon).scaledToWidth(16));
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
        menu(QWidget* parent)
            : QFrame(parent)
            , widget_origin_{ nullptr }
        {
            //setAttribute(Qt::WA_ShowWithoutActivating);
            setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

            layout_ = new nxw::vbox_layout;
            layout_->setAlignment(layout_, Qt::AlignTop);

            setLayout(layout_);
        }

        void clear()
        {
            while (auto item = layout_->takeAt(0))
            {
                delete item->widget();
            }
        }

        template<class Widget, class... Args>
        void add(Args&&... args)
        {
            auto widget = new Widget(std::forward<Args>(args)...);
            layout_->addWidget(widget);
            adjustSize();
        }

        void add(const nxi::command& command)
        {
            add<nxw::menu_item>(command.name(), command.function(), command.icon());
        }

        void add(const QString& action_name, std::function<void()> function)
        {
            add<nxw::menu_item>(action_name, std::move(function));
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
            QPoint position = QCursor::pos();

            if (widget_origin_)
            {
                // move menu to widget global position
                position = widget_origin_->mapToGlobal(widget_origin_->rect().bottomLeft());
            }

            move(position);
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