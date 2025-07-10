#include "formmainpagewidget.h"
#include "ui_formmainpagewidget.h"
#include "connectionerrorwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPalette>
#include <QColor>
#include <QString>
#include <QLineEdit>
#include <QFrame>
#include <qimage.h>
#include <QPixmap>

#include <QDebug>
#include "playercardwidget.h"
#include "playerpendingcardwidget.h"
#include "serverstatusmanager.h"
#include <algorithm>


FormMainPageWidget::FormMainPageWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormMainPageWidget)
{
    ui->setupUi(this);
    // Set the button disable because at the begging we don't have any player to analyze
    ui->pushButtonStartAnalysis->setEnabled(false);

    // Conectar con gestor de estado para recibir lista de jugadores
    auto *mgr = ServerStatusManager::instance();
    connect(mgr, &ServerStatusManager::playersUpdated,
            this, &FormMainPageWidget::onPlayersUpdated);

    // Por ahora, asumimos que no hay conexión al backend y mostramos el placeholder
    showConnectionErrorPlaceholder();

    ui->lineEditNewUser->setPlaceholderText(tr("Enter username to analyze"));

    connect(ui->lineEditNewUser,  &QLineEdit::textChanged, this, [this]() {
        if (ui->lineEditNewUser->text().isEmpty()) {
            ui->pushButtonStartAnalysis->setEnabled(false);
        } else {
            ui->pushButtonStartAnalysis->setEnabled(true);
        }
    });
    connect(ui->pushButtonStartAnalysis, &QPushButton::clicked,
            this, &FormMainPageWidget::onStartAnalysisClicked);
}

FormMainPageWidget::~FormMainPageWidget()
{
    delete ui;
}

// Implementación de createAnalysisCard adaptada de MainWindow
QWidget* FormMainPageWidget::createAnalysisCard(const QString &title, const QString &description, const QString &iconText, const QString &iconColor)
{
    auto *card = new QWidget();
    card->setFixedSize(180, 120);
    card->setStyleSheet(
        "QWidget {"
        "   background-color: #3A4B5C;"
        "   border-radius: 12px;"
        "   padding: 15px;"
        "}"
        "QWidget:hover {"
        "   background-color: #455A6B;"
        "}"
    );
    auto *layout = new QVBoxLayout(card);
    layout->setSpacing(8);
    auto *iconLabel = new QLabel(iconText);
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setStyleSheet(
        QString("color: %1; font-size: 24px; background-color: %1; color: white; "
                "border-radius: 8px; padding: 8px; max-width: 40px; max-height: 40px;").arg(iconColor)
    );
    iconLabel->setFixedSize(40, 40);
    auto *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setWordWrap(true);
    auto *descLabel = new QLabel(description);
    descLabel->setStyleSheet("color: #BDC3C7; font-size: 11px;");
    descLabel->setAlignment(Qt::AlignCenter);
    descLabel->setWordWrap(true);
    layout->addWidget(iconLabel, 0, Qt::AlignCenter);
    layout->addWidget(titleLabel);
    layout->addWidget(descLabel);
    layout->addStretch();
    return card;
}

void FormMainPageWidget::showConnectionErrorPlaceholder()
{
    if (!ui || !ui->frameAnalyzedPlayer)
        return;

    

    // Si el frame ya tiene un layout, lo limpiamos
    QLayout *oldLayout = ui->frameAnalyzedPlayer->layout();
    if (oldLayout) {
        QLayoutItem *child;
        while ((child = oldLayout->takeAt(0)) != nullptr) {
            if (child->widget()) {
                child->widget()->deleteLater();
            }
            delete child;
        }
        delete oldLayout;
    }

    // Nuevo layout centrado
    auto *layout = new QVBoxLayout(ui->frameAnalyzedPlayer);
    layout->setContentsMargins(32, 32, 32, 32);
    layout->setAlignment(Qt::AlignCenter);

    // Crear el widget de error
    auto *errorWidget = new ConnectionErrorWidget(ui->frameAnalyzedPlayer);
    connect(errorWidget, &ConnectionErrorWidget::retryClicked, this, &FormMainPageWidget::onRetryConnection);

    layout->addWidget(errorWidget);
}

void FormMainPageWidget::onRetryConnection()
{
    // Aquí se podría volver a intentar la conexión. Por ahora, simplemente volvemos a mostrar el placeholder
    showConnectionErrorPlaceholder();
}

// -----------------------------------------------------------------------------
void FormMainPageWidget::showNoPlayersPlaceholder()
{
    if (!ui || !ui->frameAnalyzedPlayer)
        return;

    clearFrame(ui->frameAnalyzedPlayer);

    auto *layout = new QVBoxLayout(ui->frameAnalyzedPlayer);
    layout->setContentsMargins(32, 32, 32, 32);
    layout->setAlignment(Qt::AlignCenter);

    // Icono usuario genérico
    auto *iconLabel = new QLabel("👤", ui->frameAnalyzedPlayer);
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setStyleSheet("font-size: 48px; color: #7F8C8D; margin: 20px 0 10px 0;");

    // Texto principal
    auto *titleLabel = new QLabel(tr("No players analyzed"), ui->frameAnalyzedPlayer);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: white; font-size: 16px; font-weight: bold;");

    // Subtexto
    auto *subtitleLabel = new QLabel(tr("Start analyzing a player to see results here"), ui->frameAnalyzedPlayer);
    subtitleLabel->setAlignment(Qt::AlignCenter);
    subtitleLabel->setStyleSheet("color: #BDC3C7; font-size: 13px;");

    layout->addWidget(iconLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(subtitleLabel);
}

// -----------------------------------------------------------------------------
void FormMainPageWidget::clearFrame(QFrame *frame)
{
    if (!frame) return;
    QLayout *oldLayout = frame->layout();
    if (oldLayout) {
        QLayoutItem *child;
        while ((child = oldLayout->takeAt(0)) != nullptr) {
            if (child->widget())
                child->widget()->deleteLater();
            delete child;
        }
        delete oldLayout;
    }
}

void FormMainPageWidget::onPlayersUpdated(const QList<PlayerInfo> &players)
{
    qDebug() << "[FormMainPageWidget] onPlayersUpdated called with" << players.size() << "players";
    // Si frame no tiene layout, creamos vertical layout principal
    if (!ui->frameAnalyzedPlayer->layout()) {
        auto *mainLayout = new QVBoxLayout(ui->frameAnalyzedPlayer);
        mainLayout->setContentsMargins(16, 16, 16, 16);
        mainLayout->setSpacing(12);
        mainLayout->addStretch();
    }

    // Ocultar placeholder si existe
    if (players.isEmpty()) {
        showNoPlayersPlaceholder();
        return;
    }

    // Actualizar/crear tarjetas
    auto *vLayout = qobject_cast<QVBoxLayout *>(ui->frameAnalyzedPlayer->layout());
    if (!vLayout) return;

    for (const auto &p : players) {
        QWidget *card = m_playerCardMap.value(p.username, nullptr);

        if (card) {
            // actualizar tarjeta existente
            qDebug() << "[FormMainPageWidget] Updating existing card for" << p.username << "status:" << p.status << "progress:" << p.progress;
            if (auto *pending = qobject_cast<PlayerPendingCardWidget *>(card))
                pending->updateInfo(p);
            // ready card por ahora no requiere updates
        } else {
            // crear nueva tarjeta
            qDebug() << "[FormMainPageWidget] Creating new card for" << p.username << "status:" << p.status;
            if (p.status.toLower() == "ready") {
                auto *readyCard = new PlayerCardWidget(p, ui->frameAnalyzedPlayer);
                connect(readyCard, &PlayerCardWidget::clicked, this, &FormMainPageWidget::onPlayerClicked);
                card = readyCard;
            } else {
                auto *pendingCard = new PlayerPendingCardWidget(p, ui->frameAnalyzedPlayer);
                connect(pendingCard, &PlayerPendingCardWidget::clicked, this, &FormMainPageWidget::onPlayerClicked);
                card = pendingCard;
            }
            vLayout->insertWidget(vLayout->count() - 1, card); // antes del stretch
            m_playerCardMap.insert(p.username, card);
        }
    }

    // Eliminar tarjetas que ya no están en la lista
    QList<QString> toRemove;
    for (const QString &uname : m_playerCardMap.keys()) {
        bool exists = std::any_of(players.begin(), players.end(), [&](const PlayerInfo &pi){ return pi.username == uname; });
        if (!exists) toRemove.append(uname);
    }
    for (const QString &uname : toRemove) {
        QWidget *w = m_playerCardMap.take(uname);
        if (w) w->deleteLater();
    }
}

void FormMainPageWidget::onPlayerClicked(const QString &username)
{
    qDebug() << "Player clicked:" << username;
}

// -----------------------------------------------------------------------------
void FormMainPageWidget::onStartAnalysisClicked()
{
    const QString user = ui->lineEditNewUser->text().trimmed();
    if (user.isEmpty()) return;

    ServerStatusManager::instance()->analyzePlayer(user);

    ui->lineEditNewUser->clear();
    ui->pushButtonStartAnalysis->setEnabled(false);
}
