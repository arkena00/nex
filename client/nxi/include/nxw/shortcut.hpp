#ifndef NXW_SHORTCUT_H_NXI
#define NXW_SHORTCUT_H_NXI

#include <QWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QListWidget>
#include <QLabel>
#include <include/nxi/core.hpp>

enum class trigger_mode
{
    sequence,
    combo
};

static int scid = 0;

struct shortcut_item
{
    int id;
    int parent_id;
    std::vector<Qt::Key> combo_keys;
    std::vector<Qt::Key> sequence_keys;
    QString name;
    QString action;

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

        void event_change(std::vector<shortcut_item>);

        static QString to_string(Qt::Key key);
        static QString to_string(shortcut_item);

    private:
        shortcut* shortcut_;

        QListWidget* view_;
        QLabel* label_;
    };

    class shortcut : public QWidget
    {
        Q_OBJECT
    public:
        shortcut(QWidget* parent) :
            QWidget(parent)
        {
            view_ = new shortcut_view(this);

            // load actions
            add(0, {}, { Qt::Key_Control, Qt::Key_F}, "find page");
            add(0, { Qt::Key_Control }, { Qt::Key_F, Qt::Key_G}, "find google");
            add(0, { Qt::Key_Control, Qt::Key_R  }, {  }, "new tab");
            add(0, { Qt::Key_Control, Qt::Key_Shift }, { Qt::Key_T, Qt::Key_R }, "restore tab");

            add(0, { }, { Qt::Key_C, Qt::Key_P, Qt::Key_P }, "find page");

            /*
             CTRL E
            (CTRL) E
            (CTRL) F F
            (CTRL R) E E

             COMBO1 + COMBO 2
             full_sequence SEQ 1    +  SEQ 2  + SEQ 3 + SEQ 4
             match_combo (SEQ.begin, SEQ.begin + COMBO_SIZE)
             match_sequence(SEQ.begin + COMBO_SIZE, SEQ.end)

            check sc.combo in input, on match sequence mode
            check sc.sequence in input*/

            untrigger();
            view_->show();

            for (auto item : shortcuts_)
            {
                view_->add(item);
            }

            current_id_ = 0;
        }
        ~shortcut() = default;

        int add(int parent_id, std::vector<Qt::Key> combo_keys, std::vector<Qt::Key> sequence_keys, QString name, QString action = "")
        {
            scid++;
            //if (parent_id == 0) triggers_.insert(keys[0]);
            shortcut_item sc;
            sc.name = name.toStdString().c_str();
            sc.id = scid;
            sc.action = "";
            sc.combo_keys = combo_keys;
            sc.sequence_keys = sequence_keys;
            sc.parent_id = parent_id;
            shortcuts_.push_back( sc );
            return scid;
        }

        void untrigger()
        {
            combo_keys_.clear();
            input_.clear();
            sequence_match_ = false;
            combo_match_ = false;
            executed_ = false;
            trigger_mode_ = trigger_mode::combo;
        }

        void exec(shortcut_item sc)
        {
            qDebug() << shortcut_view::to_string(sc).toStdString().c_str();
            untrigger();
            executed_ = true;
        }

        void process(QKeyEvent* event)
        {
            if (event->isAutoRepeat()) return;

            std::vector<shortcut_item> shortcut_match;
            std::stringstream log;
            if (event->type() == QEvent::KeyPress)
            {
                Qt::Key key = static_cast<Qt::Key>(event->key());

                // store keys
                if (trigger_mode_ == trigger_mode::combo) combo_keys_.push_back(key);
                //else sequence_keys_.push_back(key);
                input_.push_back(key);

                for (auto sc : shortcuts_)
                {
                    combo_match_ = false;
                    sequence_match_ = false;
                    bool sequence_partial_match = false;

                    // test combo + key
                    // test combo + nav + key
                    //qDebug() <<  "\nTEST : " << shortcut_view::to_string(sc).toStdString().c_str();

                    bool fullmatch = combo_keys_.size() > 0 && combo_keys_.size() <= sc.combo_keys.size()
                                     && std::equal(combo_keys_.begin(), combo_keys_.end(), sc.combo_keys.begin());

                    // combos partial match
                    bool combo_partial_match = combo_keys_.size() <= sc.combo_keys.size()
                                               && std::equal(combo_keys_.begin(), combo_keys_.end(), sc.combo_keys.begin());

                    if (combo_partial_match)
                    {
                        if (combo_keys_.size() == sc.combo_keys.size()) combo_match_ = true;
                        if (combo_match_ && sc.sequence_keys.size() == 0) return exec(sc);


                        //log << " COMBO ";
                        //log << " PMATCH " << combo_partial_match;
                        //log <<  " COMBO_MATCH " << combo_match_;

                        // sequences partial match
                        sequence_partial_match = sequence_keys_.size() <= sc.sequence_keys.size()
                                                 && std::equal(sequence_keys_.begin(), sequence_keys_.end(), sc.sequence_keys.begin());
                        if (sequence_partial_match)
                        {
                            if (sequence_keys_.size() == sc.sequence_keys.size()) sequence_match_ = true;
                            log << " SEQ ";
                            log << " PMATCH " << sequence_partial_match;
                            log <<  " MATCH " << sequence_match_;
                        }
                    }




                    // full match
                    if (combo_match_ && sequence_match_)
                    {
                        qDebug() << "exec : " << sc.name;
                        untrigger();
                    }
                    else if (combo_partial_match || sequence_partial_match)
                    {
                        shortcut_match.push_back(sc);
                    }
                    //else untrigger();
                } // for


            }
            Qt::Key key = static_cast<Qt::Key>(event->key());


            if (event->type() == QEvent::KeyRelease)
            {
                combo_keys_.erase( std::remove( combo_keys_.begin(), combo_keys_.end(), key ), combo_keys_.end() );

                if (combo_keys_.size() == 0 && sequence_keys_.size() == 0) untrigger();

                if (combo_keys_.size() > 0) trigger_mode_ = trigger_mode::sequence;
            }

            view_->event_change(shortcut_match);


            qDebug() << "___COMBO";
            for (auto k : combo_keys_) qDebug() << k;

            qDebug() << "___INPUT";
            for (auto k : input_) qDebug() << k;

            //qDebug() << log.str().c_str();
        }

    private:
        std::vector<shortcut_item> shortcuts_;
        shortcut_view* view_;

        std::vector<Qt::Key> input_;

        std::vector<Qt::Key> sequence_keys_;
        std::vector<Qt::Key> combo_keys_;

        std::unordered_set<Qt::Key> triggers_;
        bool match_;
        trigger_mode trigger_mode_;
        int sequencing_;
        Qt::Key trigger_key_;
        int current_id_;
        bool combo_match_;
        bool sequence_match_;
        bool executed_;
    };
} // nxw

#endif // NXW_SHORTCUT_H_NXI