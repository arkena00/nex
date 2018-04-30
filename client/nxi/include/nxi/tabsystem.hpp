#ifndef NXI_TABSYSTEM_H_NXI
#define NXI_TABSYSTEM_H_NXI

#include <nxs/network/client.hpp>

#include <QObject>
#include <QVector>
#include <QString>

namespace nxi
{
    struct tab
    {
        tab() : name{ "default_tab" } {}

        QString name;
    };

    class tabsystem : public QObject
    {
        Q_OBJECT
    public:
        void on_add(QWidget* source);

        void on_change(QWidget* source, int index);

    signals:
        void event_add(QWidget* source, nxi::tab);
        void event_change(QWidget* source, int index);

    private:
        QVector<nxi::tab> tabs_;
    };
} // nxi

#endif // NXI_TABSYSTEM_H_NXI