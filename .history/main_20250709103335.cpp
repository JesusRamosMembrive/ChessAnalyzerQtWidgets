#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Crea el monitor de estado del backend (singleton). Esto lanza un chequeo inicial.
    ServerStatusManager::instance();
    MainWindow w;
    w.show();
    return a.exec();
}
