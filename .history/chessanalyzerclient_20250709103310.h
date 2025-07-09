// ChessAnalyzerClient.h
// -----------------------------------------------------------------------------
// Cliente Qt6 para la API descrita en app/main.py (Chess Analyzer API).
// Ofrece métodos asíncronos para invocar los endpoints REST expuestos por FastAPI
// empleando únicamente clases de Qt (QNetworkAccessManager, QJson*, etc.).
// -----------------------------------------------------------------------------
// © 2025  — Licencia MIT.  Puedes usar, modificar y redistribuir libremente.
// -----------------------------------------------------------------------------
#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QUrlQuery>
#include <QPointer>

//!  \brief Cliente ligero para la Chess Analyzer API basado en Qt6.
//!
//!  *Todas* las peticiones son asíncronas.  Cuando la respuesta llega se emiten
//!  las señales requestSucceeded() o requestFailed() según corresponda.  De
//!  este modo el hilo de UI nunca se bloquea.
//!
//!  Ejemplo de uso (en un QObject cualquiera):
//!  ```cpp
//!  auto *client = new ChessAnalyzerClient(QUrl("http://localhost:8000"), this);
//!  connect(client, &ChessAnalyzerClient::requestSucceeded, this,
//!          [](const QString &ep, const QJsonObject &data) {
//!              qInfo() << "[OK]" << ep << data;
//!          });
//!  connect(client, &ChessAnalyzerClient::requestFailed, this,
//!          [](const QString &ep, const QString &err, int code) {
//!              qWarning() << "[FAIL]" << ep << code << err;
//!          });
//!
//!  client->getHealth();
//!  ```
class ChessAnalyzerClient : public QObject
{
    Q_OBJECT
public:
    /// Crea un cliente apuntando a \a baseUrl.  Por defecto se asume
    /// "http://localhost:8000" (sin sufijo /api/v1; los métodos lo añaden).
    explicit ChessAnalyzerClient(const QUrl &baseUrl = QUrl("http://localhost:8000"),
                                 QObject *parent = nullptr);

    // ---------------------------------------------------------------------
    // Endpoints principales (alias legibles)
    // ---------------------------------------------------------------------
    void getHealth();                                                      ///< GET  /api/v1/health
    void analyzeGame(const QString &pgn, const QList<int> &moveTimes = {}); ///< POST /analyze (legacy path — mantiene compat.)
    void getTaskStatus(const QString &taskId);                             ///< GET  /tasks/{taskId}
    void stopTask(const QString &taskId);                                  ///< DELETE /tasks/{taskId}
    void getGame(int gameId);                                              ///< GET  /games/{gameId}
    void stopGameAnalysis(int gameId, const QString &taskId);              ///< POST /games/{id}/stop

    void analyzePlayer(const QString &username, int months = 12);          ///< POST /players/{username}?months=N
    void getPlayer(const QString &username);                               ///< GET  /players/{username}
    void stopPlayerAnalysis(const QString &username);                      ///< POST /players/{username}/stop
    void listPlayers(const QString &status = QString());                   ///< GET  /players[?status=pending|ready|error]
    void getPlayerMetrics(const QString &username);                        ///< GET  /metrics/player/{username}

signals:
    /// Se emite cuando una petición termina con éxito.
    /// @param endpoint Ruta relativa solicitada (por ej. "/api/v1/health").
    /// @param data     Cuerpo JSON ya parseado.
    void requestSucceeded(const QString &endpoint, const QJsonObject &data);

    /// Se emite cuando una petición devuelve código HTTP >= 400 o un error de red.
    /// @param endpoint Ruta relativa solicitada.
    /// @param errorString Descripción del error.
    /// @param httpStatus  Código HTTP (o -1 si es error de red).
    void requestFailed(const QString &endpoint, const QString &errorString, int httpStatus);

private slots:
    void onReplyFinished();

private:
    void sendRequest(const QString &relativePath,
                     QNetworkAccessManager::Operation op,
                     const QJsonObject &payload = QJsonObject(),
                     const QUrlQuery &query = {});

    QUrl m_baseUrl;              ///< Ej. http://localhost:8000
    QNetworkAccessManager m_nam; ///< Gestor de peticiones asíncronas.
};

// =============================================================================
// IMPLEMENTACIÓN INLINE
// =============================================================================

// NUEVO: constructor ----------------------------------------------------------
inline ChessAnalyzerClient::ChessAnalyzerClient(const QUrl &baseUrl, QObject *parent)
    : QObject(parent), m_baseUrl(baseUrl)
{
    // Aseguramos que el QNetworkAccessManager tenga este objeto como padre.
    m_nam.setParent(this);
}

inline void ChessAnalyzerClient::getHealth()
{
    sendRequest("/api/v1/health", QNetworkAccessManager::GetOperation);
}

inline void ChessAnalyzerClient::analyzeGame(const QString &pgn, const QList<int> &moveTimes)
{
    QJsonObject obj;
    obj.insert("pgn", pgn);
    if (!moveTimes.isEmpty()) {
        QJsonArray arr;
        for (int ms : moveTimes)
            arr.append(ms);
        obj.insert("move_times", arr);
    }
    // Legacy path para compatibilidad con test-suite existente.
    sendRequest("/analyze", QNetworkAccessManager::PostOperation, obj);
}

inline void ChessAnalyzerClient::getTaskStatus(const QString &taskId)
{
    sendRequest(QString("/tasks/%1").arg(taskId), QNetworkAccessManager::GetOperation);
}

inline void ChessAnalyzerClient::stopTask(const QString &taskId)
{
    sendRequest(QString("/tasks/%1").arg(taskId), QNetworkAccessManager::DeleteOperation);
}

inline void ChessAnalyzerClient::getGame(int gameId)
{
    sendRequest(QString("/games/%1").arg(gameId), QNetworkAccessManager::GetOperation);
}

inline void ChessAnalyzerClient::stopGameAnalysis(int gameId, const QString &taskId)
{
    QJsonObject body; body.insert("task_id", taskId);
    sendRequest(QString("/games/%1/stop").arg(gameId), QNetworkAccessManager::PostOperation, body);
}

inline void ChessAnalyzerClient::analyzePlayer(const QString &username, int months)
{
    QUrlQuery q; q.addQueryItem("months", QString::number(months));
    sendRequest(QString("/players/%1").arg(username), QNetworkAccessManager::PostOperation, QJsonObject(), q);
}

inline void ChessAnalyzerClient::getPlayer(const QString &username)
{
    sendRequest(QString("/players/%1").arg(username), QNetworkAccessManager::GetOperation);
}

inline void ChessAnalyzerClient::stopPlayerAnalysis(const QString &username)
{
    sendRequest(QString("/players/%1/stop").arg(username), QNetworkAccessManager::PostOperation);
}

inline void ChessAnalyzerClient::listPlayers(const QString &status)
{
    QUrlQuery q; if (!status.isEmpty()) q.addQueryItem("status", status);
    sendRequest("/players", QNetworkAccessManager::GetOperation, QJsonObject(), q);
}

inline void ChessAnalyzerClient::getPlayerMetrics(const QString &username)
{
    sendRequest(QString("/metrics/player/%1").arg(username), QNetworkAccessManager::GetOperation);
}

// -----------------------------------------------------------------------------
// Helper interno común a TODOS los métodos públicos
// -----------------------------------------------------------------------------
inline void ChessAnalyzerClient::sendRequest(const QString &relativePath,
                                             QNetworkAccessManager::Operation op,
                                             const QJsonObject &payload,
                                             const QUrlQuery &query)
{
    QUrl url = m_baseUrl;
    url.setPath(url.path() + relativePath);
    if (!query.isEmpty())
        url.setQuery(query);

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = nullptr;
    switch (op) {
    case QNetworkAccessManager::GetOperation:
        reply = m_nam.get(req);
        break;
    case QNetworkAccessManager::PostOperation:
        reply = m_nam.post(req, QJsonDocument(payload).toJson());
        break;
    case QNetworkAccessManager::PutOperation:
        reply = m_nam.put(req, QJsonDocument(payload).toJson());
        break;
    case QNetworkAccessManager::DeleteOperation:
        reply = m_nam.deleteResource(req);
        break;
    default:
        Q_ASSERT_X(false, "ChessAnalyzerClient", "Unsupported HTTP verb");
    }

    // Guardamos la ruta para identificar el reply.
    reply->setProperty("endpoint", relativePath);

    connect(reply, &QNetworkReply::finished, this, &ChessAnalyzerClient::onReplyFinished);
}

inline void ChessAnalyzerClient::onReplyFinished()
{
    QPointer<QNetworkReply> reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply)
        return; // Debiera no ocurrir.

    const QString endpoint = reply->property("endpoint").toString();
    const int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (reply->error() == QNetworkReply::NoError && statusCode < 400) {
        const QByteArray data = reply->readAll();
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(data, &err);
        if (err.error != QJsonParseError::NoError) {
            emit requestFailed(endpoint, tr("JSON parse error: %1").arg(err.errorString()), statusCode);
        } else {
            emit requestSucceeded(endpoint, doc.object());
        }
    } else {
        emit requestFailed(endpoint, reply->errorString(), statusCode > 0 ? statusCode : -1);
    }

    reply->deleteLater();
}
