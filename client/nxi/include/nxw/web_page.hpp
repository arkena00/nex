#ifndef NXW_WEB_PAGE_H_NXI
#define NXW_WEB_PAGE_H_NXI

#include <ui/interface.hpp>


#include <QWebEnginePage>

namespace nxw
{
    class web_page : QWidget
    {
    Q_OBJECT
    public:
        web_page(QWidget* parent = nullptr)
        {
            page_ = new QWebEnginePage(this);
        }

        void load_url(const QString& url){}
        void load(const QString& data){page_->setUrl(QUrl(data));}

    private:
        QWebEnginePage* page_;
    };

} // nxw

#endif // NXW_WEB_PAGE_H_NXI