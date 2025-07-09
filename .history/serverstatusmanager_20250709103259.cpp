#include "serverstatusmanager.h"

#include <QPointer>

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
            [this](const QString &endpoint, const QJsonObject &) {
                if (endpoint == "/api/v1/health")
                    setStatus(Status::Online);
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
} 