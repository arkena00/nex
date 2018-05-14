#ifndef NXW_SHORTCUT_H_NXI
#define NXW_SHORTCUT_H_NXI

#include <QWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QListWidget>
#include <QLabel>
#include <include/nxi/core.hpp>

struct shortcut_item
{
    QString name;
    std::vector<Qt::Key> seq;

    shortcut_item(const char* name_, std::vector<Qt::Key> seq_) :
        name{ name_ },
        seq{ seq_ }
    {}
};


namespace nxw
{
    class shortcut;

    class shortcut_view : public QWidget
    {
    public:
        shortcut_view(shortcut* shortcut);

        void keyPressEvent(QKeyEvent* event) override;
        void keyReleaseEvent(QKeyEvent* event) override;
        void showEvent(QShowEvent*) override;
        void add(shortcut_item);

        void event_sequence_end();
        void event_change(std::vector<Qt::Key>);

    private:
        shortcut* shortcut_;

        QListWidget* view_;
        QLabel* label_;
    };

    class shortcut : public QWidget
    {
        Q_OBJECT
    public:
        shortcut(QWidget* parent, nxi::core& nxi_core) :
            QWidget(parent)
        {
            view_ = new shortcut_view(this);

            // load actions
            actions_.push_back(shortcut_item{ "T - new tab", { Qt::Key_T } });
            actions_.push_back(shortcut_item{ "F - find text", { Qt::Key_F } });
            actions_.push_back(shortcut_item{ "G - find on google", { Qt::Key_G } });

            trigger_key_ = Qt::Key_Control;
            untrigger_key_ = Qt::Key_Alt;

            for (auto item : actions_)
            {
                view_->add(item);
            }

        }
        ~shortcut() = default;

        void sequence_start()
        {
            trigger_ = true;
            view_->show();
        }

        void sequence_end()
        {
            trigger_ = false;
            input_.clear();
            view_->hide();
            view_->event_change(input_);
        }

        void process(QKeyEvent* event)
        {
            Qt::Key key = static_cast<Qt::Key>(event->key());

            if (event->type() == QEvent::KeyPress)
            {
                input_.push_back(key);

                if (key == trigger_key_) sequence_start();
                if (key == untrigger_key_) sequence_end();

                for (auto action : actions_)
                {
                    // match, reset
                    if (action.seq[0] == key)
                    {
                        qDebug() << action.name;
                        sequence_end();
                        break;
                    }
                }
                view_->event_change(input_);
            }

            if (event->type() == QEvent::KeyRelease)
            {
                if (key == untrigger_key_) sequence_end();
            }


        }

    private:
        std::vector<shortcut_item> actions_;
        shortcut_view* view_;

        std::vector<Qt::Key> input_;

        bool trigger_;
        Qt::Key trigger_key_;
        Qt::Key untrigger_key_;
    };
} // nxw

#endif // NXW_SHORTCUT_H_NXI