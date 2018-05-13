#ifndef NXW_TABWIDGET_H_NXI
#define NXW_TABWIDGET_H_NXI

#include <nxw/tabdata_base.hpp>

#include <QStackedWidget>
#include <QVector>
#include <QWidget>

#include <utility>
#include <memory>

namespace nxi { class tabsystem; }
namespace nxw { class tab_base; }

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

        void change(int index);
        void data_add(std::unique_ptr<nxw::tabdata_base>);
        void tabchanger_add(nxw::tabchanger*);
        void icon_set(int index, const QIcon& icon);
        void icon_set(nxw::tab_base* tab, const QIcon& icon);
        void title_set(int index, const QString& title);
        void title_set(nxw::tab_base* tab, const QString& title);

        int index(nxw::tab_base*) const;

        const nxw::tabdata_base& tabdata() const;
        QWidget* widget();

    private:
        nxi::tabsystem& tabsystem_;

        QVector<nxw::tabchanger*> tabchangers_;
        QStackedWidget* tabstack_;
        std::unique_ptr<nxw::tabdata_base> tabdata_;
    };
} // nxw

#endif // NXW_TABWIDGET_H_NXI