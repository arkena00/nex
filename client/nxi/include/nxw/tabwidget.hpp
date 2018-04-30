#ifndef NXW_TABWIDGET_H_NXI
#define NXW_TABWIDGET_H_NXI

#include <QHash>
#include <QStackedWidget>
#include <QVector>
#include <QWidget>

#include <utility>

namespace nxi { class tabsystem; }
namespace ui { struct tabdata; class tab_base; }

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
        void change(int index);
        void icon_set(int index, const QIcon& icon);
        void title_set(int index, const QString& title);

        int index(ui::tab_base*) const;
        QWidget* widget();

    public:
        nxi::tabsystem& tabsystem_;

        QVector<nxw::tabchanger*> tabchangers_;
        QStackedWidget* tabstack_;
        ui::tabdata* tabdata_;
    };
} // nxw

#endif // NXW_TABWIDGET_H_NXI