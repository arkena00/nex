#ifndef NXI_TABSYSTEM_H_NXI
#define NXI_TABSYSTEM_H_NXI

#include <nxs/network/client.hpp>
#include <QWidget>
#include <QDebug>

namespace nxi
{
    class tabsystem : public QObject
    {
        Q_OBJECT
    public:
        void on_add(QWidget* source)
        {
            tabs_.push_back(source);

            qDebug() << "tabsystem on_add from" << source->windowTitle();
            emit event_add(source);
        }

        signals:
        void event_add(QWidget*);

    private:
        QVector<QWidget*> tabs_;
    };
} // nxi

#endif // NXI_TABSYSTEM_H_NXI