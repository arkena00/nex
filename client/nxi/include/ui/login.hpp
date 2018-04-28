#ifndef UI_LOGIN_H_NXI
#define UI_LOGIN_H_NXI

#include <QWidget>

#include <QLineEdit>
#include <QImage>
#include <QPainter>
#include <QGridLayout>

#include <ui/window.hpp>

namespace ui
{
    class login : public QWidget
    {
    Q_OBJECT

    private:
        QLineEdit* login_;

        void login::paintEvent(QPaintEvent *e)
        {
            QPainter painter(this);
            painter.drawPixmap(0, 0, QPixmap(":/image/login_background").scaled(size()));
            QWidget::paintEvent(e);
        }

    public:
        login(ui::window* window) : QWidget(window)
        {
            login_ = new QLineEdit(this);
            login_->setText("ads00");

            auto layout = new QGridLayout;
            layout->addWidget(login_, 0, 0, Qt::AlignCenter);

            QObject::connect(login_, &QLineEdit::returnPressed, this, [window, this]()
            {
                deleteLater();
                window->load<ui::main>();
            });

            setLayout(layout);
        }

    };

} // ui

#endif // UI_LOGIN_H_NXI
