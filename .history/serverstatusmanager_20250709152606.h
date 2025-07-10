#pragma once

#include <QObject>
#include "chessanalyzerclient.h"
#include <QDateTime>
#include <QHash>
#include <QTimer>

struct PlayerInfo {
    QString   username;
    QString   status;
    int       progress {0};
    int       totalGames {0};
    int       doneGames {0};
    QDateTime requestedAt;
    QDateTime finishedAt;
};

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

    //! Lista actual de jugadores analizados/devueltos por el backend.
    const QList<PlayerInfo> &players() const { return m_players; }

signals:
    //! Se emite cuando el estado cambia respecto al anterior.
    void statusChanged(ServerStatusManager::Status newStatus);

    //! Nueva lista recibida o modificada.
    void playersUpdated(const QList<PlayerInfo> &players);

private:
    explicit ServerStatusManager(QObject *parent = nullptr);
    void setStatus(Status s);
    void parsePlayersArray(const QJsonArray &arr);
    void handlePlayerObject(const QJsonObject &obj);
    void startPolling(const QString &user);
    void stopPolling(const QString &user);

    ChessAnalyzerClient m_client;
    Status              m_status { Status::Unknown };
    QList<PlayerInfo>   m_players;
    QHash<QString, QTimer*> m_pollTimers;
}; 