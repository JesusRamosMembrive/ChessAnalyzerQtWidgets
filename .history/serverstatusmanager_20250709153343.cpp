#include "serverstatusmanager.h"

#include <QPointer>
#include <QJsonArray>
#include <QRegularExpression>

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
                    } else if (data.contains("array") && data.value("array").isArray()) {
                        parsePlayersArray(data.value("array").toArray());
                    }
                } else if (endpoint.startsWith("/players/")) {
                    // Respuesta de polling de un jugador concreto
                    handlePlayerObject(data);
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
        PlayerInfo p;
        const QJsonObject obj = val.toObject();
        p.username = obj.value("username").toString();
        p.status   = obj.value("status").toString();
        p.progress = obj.value("progress").toInt();
        p.totalGames = obj.value("total_games").toInt();
        p.doneGames  = obj.value("done_games").toInt();
        p.requestedAt = QDateTime::fromString(obj.value("requested_at").toString(), Qt::ISODate);
        p.finishedAt  = QDateTime::fromString(obj.value("finished_at").toString(), Qt::ISODate);
        list.append(p);

        if (p.status.toLower() == "pending")
            startPolling(p.username);
        else
            stopPolling(p.username);
    }

    m_players = list;
    emit playersUpdated(m_players);
}

// -----------------------------------------------------------------------------
void ServerStatusManager::handlePlayerObject(const QJsonObject &obj)
{
    if (!obj.contains("username")) return;
    const QString user = obj.value("username").toString();

    // actualizar o añadir en m_players
    bool found = false;
    for (auto &p : m_players) {
        if (p.username == user) {
            p.status = obj.value("status").toString();
            p.progress = obj.value("progress").toInt();
            p.totalGames = obj.value("total_games").toInt();
            p.doneGames = obj.value("done_games").toInt();
            p.requestedAt = QDateTime::fromString(obj.value("requested_at").toString(), Qt::ISODate);
            p.finishedAt = QDateTime::fromString(obj.value("finished_at").toString(), Qt::ISODate);
            found = true;
            break;
        }
    }
    if (!found) {
        PlayerInfo p;
        p.username = user;
        p.status = obj.value("status").toString();
        p.progress = obj.value("progress").toInt();
        p.totalGames = obj.value("total_games").toInt();
        p.doneGames = obj.value("done_games").toInt();
        p.requestedAt = QDateTime::fromString(obj.value("requested_at").toString(), Qt::ISODate);
        p.finishedAt = QDateTime::fromString(obj.value("finished_at").toString(), Qt::ISODate);
        m_players.append(p);
    }

    // gestionar timers según nuevo estado
    QString status = obj.value("status").toString().toLower();
    if (status == "pending")
        startPolling(user);
    else
        stopPolling(user);

    emit playersUpdated(m_players);
}

// -----------------------------------------------------------------------------
void ServerStatusManager::startPolling(const QString &user)
{
    if (m_pollTimers.contains(user))
        return; // ya activo

    QTimer *t = new QTimer(this);
    t->setInterval(1000);
    connect(t, &QTimer::timeout, this, [this, user]() {
        m_client.getPlayer(user);
    });
    connect(t, &QObject::destroyed, this, [this, user]() {
        m_pollTimers.remove(user);
    });
    t->start();
    m_pollTimers.insert(user, t);
}

void ServerStatusManager::stopPolling(const QString &user)
{
    if (!m_pollTimers.contains(user))
        return;
    QTimer *t = m_pollTimers.take(user);
    if (t)
        t->deleteLater();
}

// -----------------------------------------------------------------------------
void ServerStatusManager::analyzePlayer(const QString &username)
{
    if (username.trimmed().isEmpty())
        return;

    m_client.analyzePlayer(username.trimmed());

    // Añadir placeholder en lista si no existe
    bool found = false;
    for (auto &p : m_players) {
        if (p.username.compare(username, Qt::CaseInsensitive) == 0) {
            found = true;
            p.status = "pending";
            p.progress = 0;
            p.doneGames = 0;
            break;
        }
    }
    if (!found) {
        PlayerInfo p;
        p.username = username;
        p.status = "pending";
        p.progress = 0;
        p.totalGames = 0;
        p.doneGames = 0;
        p.requestedAt = QDateTime::currentDateTimeUtc();
        m_players.append(p);
    }

    startPolling(username);
    emit playersUpdated(m_players);
} 