#ifndef NXW_TABWIDGET_H_NXI
#define NXW_TABWIDGET_H_NXI

#include <QWidget>
#include <QVector>
#include <QHash>

#include <utility>

class QStackedWidget;

namespace nxi { class tabsystem; }
namespace ui { struct tabdata; }

namespace nxw
{

    class tabchanger;

    class tabwidget : public QWidget
    {
        Q_OBJECT
    public:
        tabwidget(QWidget* parent, nxi::tabsystem&);
        ~tabwidget();


        template<class T, class... Args>
        T* add(Args&&... args)
        {
            auto t = new T(std::forward<Args>(args)...);
            tabstack_->addWidget(t);

            return t;
         }

        void tabchanger_add(nxw::tabchanger*);

        QWidget* widget();

        void change(int index);


    public:
        nxi::tabsystem& tabsystem_;

        QVector<nxw::tabchanger*> tabchangers_;
        QStackedWidget* tabstack_;
        ui::tabdata* tabdata_;
    };
} // nxw

#endif // NXW_TABWIDGET_H_NXI