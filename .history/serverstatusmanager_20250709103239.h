#pragma once

#include <QObject>
#include "chessanalyzerclient.h"

//!  \brief Monitoriza la disponibilidad del servidor Chess Analyzer y expone su estado.
//!
//!  Se crea un *singleton* accesible mediante instance(). Al arrancar la aplicación
//!  intenta conectarse al endpoint `/api/v1/health`.  Tras la respuesta emite
//!  la señal statusChanged() con el nuevo estado.
class ServerStatusManager : public QObject
{
    Q_OBJECT
public:
    enum class Status {
        Unknown,   ///< Estado inicial – aún no se ha intentado conectar.
        Online,    ///< El servidor respondió correctamente.
        Offline    ///< Fallo al conectar o código HTTP >= 400.
    };
    Q_ENUM(Status)

    //! Acceso global al gestor (patrón Singleton *thread-safe* a nivel C++11).
    static ServerStatusManager *instance();

    Status status() const { return m_status; }
    bool   isOnline() const { return m_status == Status::Online; }

    //! Fuerza un nuevo chequeo de salud.
    void retry();

signals:
    //! Se emite cuando el estado cambia respecto al anterior.
    void statusChanged(ServerStatusManager::Status newStatus);

private:
    explicit ServerStatusManager(QObject *parent = nullptr);
    void setStatus(Status s);

    ChessAnalyzerClient m_client;
    Status              m_status { Status::Unknown };
}; 