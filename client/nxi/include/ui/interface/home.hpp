#ifndef UI_INTERFACE_HOME_H_NXI
#define UI_INTERFACE_HOME_H_NXI

#include <QStackedWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QtGui/qpainter.h>

#include <QTabBar>

#include <ui/window.hpp>
#include <ui/interface.hpp>



namespace ui
{
    namespace interfaces
    {

        class home : public ui::interface
        {
        Q_OBJECT

        private:
            QLineEdit* login_;

            void home::paintEvent(QPaintEvent *e)
            {
                QPainter painter(this);
                painter.drawPixmap(0, 0, QPixmap(":/image/login_background").scaled(size()));
                QWidget::paintEvent(e);
            }

        public:
            //operator QWidget*() { return this->widget(); }

            // ui::interface
            home()
            {
                login_ = new QLineEdit(this);
                login_->setText("ads00");

                auto layout = new QGridLayout;
                layout->addWidget(login_, 0, 0, Qt::AlignCenter);

                QObject::connect(login_, &QLineEdit::returnPressed, this, [this]()
                {
                    deleteLater();
                    //window->load<ui::main>();
                });

                setLayout(layout);
            }

        };
    }


} // ui

#endif