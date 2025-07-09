#include "mainwindow.h"
#include "serverstatusmanager.h"
#include <QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Crea el monitor de estado del backend (singleton). Esto lanza un chequeo inicial.
    auto *statusMgr = ServerStatusManager::instance();

    // Imprime estado inicial (probablemente Unknown hasta que responda el servidor)
    {
        const char *names[] = {"Unknown", "Online", "Offline"};
        qDebug() << "[Startup] Server status:" << names[static_cast<int>(statusMgr->status())];
    }

    // Escucha cambios y los muestra por consola
    QObject::connect(statusMgr, &ServerStatusManager::statusChanged,
                     [](ServerStatusManager::Status s) {
                         const char *names[] = {"Unknown", "Online", "Offline"};
                         qDebug() << "[ServerStatusManager] Status changed to" << names[static_cast<int>(s)];
                     });
    MainWindow w;
    w.show();
    return a.exec();
}
