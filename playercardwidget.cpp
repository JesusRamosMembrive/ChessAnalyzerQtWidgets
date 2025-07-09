#include "playercardwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>

PlayerCardWidget::PlayerCardWidget(const PlayerInfo &info, QWidget *parent)
    : QFrame(parent)
{
    setObjectName("playerCardWidget");
    setCursor(Qt::PointingHandCursor);
    setStyleSheet(R"(
        #playerCardWidget {
            background-color: #2C3E50;
            border-radius: 8px;
            padding: 12px;
            margin: 5px 0;
        }
        QLabel#avatar {
            background-color: #3498DB;
            color: white;
            border-radius: 16px;
            font-size: 14px;
            font-weight: bold;
        }
        QLabel#statusLabel {
            background-color: #2ECC71;
            color: white;
            border-radius: 10px;
            padding: 4px 8px;
            font-size: 11px;
            font-weight: bold;
        }
        QPushButton#deleteBtn {
            background-color: transparent;
            border: none;
            color: #E74C3C;
            font-size: 14px;
        }
        QPushButton#deleteBtn:hover {
            background-color: #E74C3C;
            color: white;
            border-radius: 4px;
        }
    )");

    buildUi(info);
}

void PlayerCardWidget::buildUi(const PlayerInfo &info)
{
    m_username = info.username;

    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(12);

    // Avatar
    m_avatarLabel = new QLabel(QString(info.username.left(1)).toUpper(), this);
    m_avatarLabel->setObjectName("avatar");
    m_avatarLabel->setFixedSize(32, 32);
    m_avatarLabel->setAlignment(Qt::AlignCenter);

    // Info usuario
    auto *infoLayout = new QVBoxLayout();
    infoLayout->setSpacing(2);

    m_nameLabel = new QLabel(info.username, this);
    m_nameLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");

    m_gamesLabel = new QLabel(QString("Games: %1    Done: %2")
                              .arg(info.totalGames)
                              .arg(info.doneGames),
                              this);
    m_gamesLabel->setStyleSheet("color: #BDC3C7; font-size: 11px;");

    infoLayout->addWidget(m_nameLabel);
    infoLayout->addWidget(m_gamesLabel);

    // Status
    m_statusLabel = new QLabel(info.status, this);
    m_statusLabel->setObjectName("statusLabel");
    m_statusLabel->setAlignment(Qt::AlignCenter);

    // Fecha
    const QString finishedStr = info.finishedAt.isValid() ? info.finishedAt.date().toString("d/M/yyyy") : "-";
    m_dateLabel = new QLabel("📅 Finished: " + finishedStr, this);
    m_dateLabel->setStyleSheet("color: #BDC3C7; font-size: 11px;");

    // Botón eliminar (sin funcionalidad aún)
    m_deleteButton = new QPushButton("🗑️", this);
    m_deleteButton->setObjectName("deleteBtn");
    m_deleteButton->setFixedSize(30, 30);

    // Ensamblar layout
    layout->addWidget(m_avatarLabel);
    layout->addLayout(infoLayout);
    layout->addStretch();
    layout->addWidget(m_statusLabel);
    layout->addWidget(m_dateLabel);
    layout->addWidget(m_deleteButton);
}

void PlayerCardWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked(m_username);

    QFrame::mousePressEvent(event);
} 