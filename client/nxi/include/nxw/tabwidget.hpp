#ifndef NXW_TABWIDGET_H_NXI
#define NXW_TABWIDGET_H_NXI

#include <QStackedWidget>
#include <ui/tab.hpp>

#include <QWidget>
#include <QVector>
#include <QDebug>
#include <QHash>

#include <utility>


namespace nxw
{
    class tabwidget : public QWidget
    {
        Q_OBJECT
    public:
        tabwidget(QWidget* parent = nullptr);
        ~tabwidget();

        template<class T, class... Args>
        T* add(Args&&... args)
        {
            auto t = new T(std::forward<Args>(args)...);
            tab_stack_->addWidget(t);
            return t;
         }

        QWidget* current_tab()
        {
            return tab_stack_->currentWidget();
        }

        QStackedWidget* stack() { return tab_stack_; }


        void on_change(int index);

    public:
        int current_index_;
        QStackedWidget* tab_stack_;

        QHash<int, QLayout*> layout_;

        QWidget* widget_ = nullptr;
    };
} // nxw

#endif // NXW_TABWIDGET_H_NXI