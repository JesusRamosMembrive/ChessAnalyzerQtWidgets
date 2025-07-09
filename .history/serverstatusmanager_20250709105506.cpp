#include "serverstatusmanager.h"

#include <QPointer>
#include <QJsonArray>

// -----------------------------------------------------------------------------
// Implementación Singleton
// -----------------------------------------------------------------------------
ServerStatusManager *ServerStatusManager::instance()
{
    static ServerStatusManager inst; // Se construye la primera vez de forma *thread-safe* (C++11)
    return &inst;
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------
ServerStatusManager::ServerStatusManager(QObject *parent)
    : QObject(parent),
      m_client(QUrl("http://localhost:8000"), this),
      m_status(Status::Unknown)
{
    // Conectar señales del cliente para actualizar estado
    connect(&m_client, &ChessAnalyzerClient::requestSucceeded, this,
            [this](const QString &endpoint, const QJsonObject &data) {
                if (endpoint == "/api/v1/health") {
                    setStatus(Status::Online);
                } else if (endpoint == "/players") {
                    // Se recibe un array; el backend lo envía dentro de un objeto con key "players"
                    // o como array raíz. Admitimos ambos.
                    if (data.contains("players") && data.value("players").isArray()) {
                        parsePlayersArray(data.value("players").toArray());
                    } else {
                        // Si la raíz no es array, data puede estar vacío (depende del backend FastAPI).
                        // En este caso intentamos convertir el documento completo a array.
                        // Para ello necesitamos el documento original; usamos sender->readAll() antes, pero
                        // aquí ya no está disponible. Por simplicidad, asumimos que la API usa la forma {"players": [...]}.
                    }
                }
            });

    connect(&m_client, &ChessAnalyzerClient::requestFailed, this,
            [this](const QString &endpoint, const QString & /*err*/, int /*code*/) {
                if (endpoint == "/api/v1/health")
                    setStatus(Status::Offline);
            });

    // Primer chequeo inmediatamente.
    m_client.getHealth();
}

// -----------------------------------------------------------------------------
void ServerStatusManager::retry()
{
    m_client.getHealth();
}

// -----------------------------------------------------------------------------
void ServerStatusManager::setStatus(Status s)
{
    if (s == m_status)
        return;

    m_status = s;
    emit statusChanged(m_status);

    // Cuando pasamos a Online solicitamos la lista de jugadores.
    if (m_status == Status::Online) {
        m_client.listPlayers();
    }
}

// -----------------------------------------------------------------------------
void ServerStatusManager::parsePlayersArray(const QJsonArray &arr)
{
    QList<PlayerInfo> list;
    for (const auto &val : arr) {
        if (!val.isObject()) continue;
        const QJsonObject obj = val.toObject();
        PlayerInfo p;
        p.username = obj.value("username").toString();
        p.status   = obj.value("status").toString();
        p.progress = obj.value("progress").toInt();
        p.totalGames = obj.value("total_games").toInt();
        p.doneGames  = obj.value("done_games").toInt();
        p.requestedAt = QDateTime::fromString(obj.value("requested_at").toString(), Qt::ISODate);
        p.finishedAt  = QDateTime::fromString(obj.value("finished_at").toString(), Qt::ISODate);
        list.append(p);
    }

    m_players = list;
    emit playersUpdated(m_players);
} 