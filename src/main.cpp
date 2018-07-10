#include <qt_directory_hook/application_window.h>
#include <QApplication>


int main(int argc, char **argv)
{
    setlocale(LC_ALL, "en-US");

    QApplication::setApplicationName("Directory Changes Hook");
    QApplication app(argc, argv);

    DirHookApplicationWindow wnd;
    static const int height = 300;
    static const int goldenRatioWidth = 300*1.6;
    wnd.setMinimumHeight(height);
    wnd.setMinimumWidth(goldenRatioWidth);
    wnd.show();

    return app.exec();
}
