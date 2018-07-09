#include <qt_directory_hook/application_window.h>
#include <QApplication>


int main(int argc, char **argv)
{
    setlocale(LC_ALL, "en-US");

    QApplication::setApplicationName("Directory Changes Hook");

    QApplication app(argc, argv);


    DirHookApplicationWindow wnd;

    wnd.setMinimumWidth(500);
    wnd.setMinimumHeight(300);

    wnd.show();

    return app.exec();
}
