#include <GL/glew.h>

#include "ui/main_window.hpp"
#include <QApplication>

using namespace e;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    MainWindow mainWindow;

    mainWindow.init({ QPoint(0, 0), QSize(800, 600) });
    mainWindow.show();

    int result = app.exec();

    return result;
}
