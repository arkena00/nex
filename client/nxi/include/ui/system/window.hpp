#ifndef UI_SYSTEM_WINDOW_H_NXI
#define UI_SYSTEM_WINDOW_H_NXI

#include <nxi/window.hpp>

#include <QObject>

namespace ui
{
	class core;
	class window;

    class window_system : public QObject
    {
        Q_OBJECT
    public:
		window_system(ui::core&);

		void unload();
        ui::window* add(const nxi::window&);
        void close(ui::window*);

        void move(ui::window*, int x, int y);
        void resize(ui::window*, int w, int h);
        void minimize(ui::window*);

        unsigned int count() const;

    private:
		ui::core& m_ui_core;

        std::vector<ui::window*> m_windows;
        //std::vector<std::pair<int, ui::window*> m_windows_storage_id;
        unsigned int m_current;
    };
} // nxi

#endif // UI_SYSTEM_WINDOW_H_NXI