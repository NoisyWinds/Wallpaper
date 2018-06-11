#include "wallpaper.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Wallpaper w;
    return a.exec();
}
