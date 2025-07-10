#include "playerpendingcardwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QMouseEvent>
#include <QDateTime>

PlayerPendingCardWidget::PlayerPendingCardWidget(const PlayerInfo &info, QWidget *parent)
    : QFrame(parent)
{
    setObjectName("playerPendingCard");
    setCursor(Qt::PointingHandCursor);

    setStyleSheet(R"(
        #playerPendingCard {
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
        QLabel#statusPending {
            background-color: transparent;
            color: #F1C40F;
            border: 1px solid #F1C40F;
            border-radius: 10px;
            padding: 2px 8px;
            font-size: 11px;
            font-weight: bold;
        }
        QProgressBar {
            background-color: #34495E;
            border-radius: 8px;
            height: 10px;
            text-align: center;
        }
        QProgressBar::chunk {
            background-color: white;
            border-radius: 8px;
        }
        QPushButton#cancelBtn {
            background-color: transparent;
            border: none;
            color: #E67E22;
            font-size: 12px;
        }
        QPushButton#cancelBtn:hover {
            background-color: #E67E22;
            color: white;
            border-radius: 4px;
        }
    )");

    buildUi(info);
}

void PlayerPendingCardWidget::buildUi(const PlayerInfo &info)
{
    m_username = info.username;

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(6);

    // Header horizontal: avatar + name + status + started date + cancel btn
    auto *headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(8);

    m_avatarLabel = new QLabel(QString(info.username.left(1)).toUpper(), this);
    m_avatarLabel->setObjectName("avatar");
    m_avatarLabel->setFixedSize(32, 32);
    m_avatarLabel->setAlignment(Qt::AlignCenter);

    m_nameLabel = new QLabel(info.username, this);
    m_nameLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");

    m_statusLabel = new QLabel("Pending", this);
    m_statusLabel->setObjectName("statusPending");
    m_statusLabel->setAlignment(Qt::AlignCenter);

    // started date
    const QString startStr = info.requestedAt.isValid() ? info.requestedAt.date().toString("d/M/yyyy") : "-";
    m_startDateLabel = new QLabel("📅 Started: " + startStr, this);
    m_startDateLabel->setStyleSheet("color: #BDC3C7; font-size: 11px;");

    // cancel button (square outline)
    m_cancelButton = new QPushButton("■", this);
    m_cancelButton->setObjectName("cancelBtn");
    m_cancelButton->setFixedSize(20, 20);

    // Build header
    headerLayout->addWidget(m_avatarLabel);
    headerLayout->addWidget(m_nameLabel);
    headerLayout->addWidget(m_statusLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(m_startDateLabel);
    headerLayout->addWidget(m_cancelButton);

    layout->addLayout(headerLayout);

    // Progress bar
    m_progressBar = new QProgressBar(this);
    m_progressBar->setRange(0, 100);
    layout->addWidget(m_progressBar);

    // Info below bar
    m_progressInfoLabel = new QLabel(this);
    m_progressInfoLabel->setStyleSheet("color: #BDC3C7; font-size: 11px;");

    m_gamesLabel = new QLabel(this);
    m_gamesLabel->setStyleSheet("color: #BDC3C7; font-size: 11px;");

    auto *infoLayout = new QHBoxLayout();
    infoLayout->addWidget(m_progressInfoLabel);
    infoLayout->addStretch();
    infoLayout->addWidget(m_gamesLabel);
    layout->addLayout(infoLayout);

    applyProgress(info.progress, info.doneGames, info.totalGames);

    connect(m_cancelButton, &QPushButton::clicked, this, [this]() {
        emit cancelRequested(m_username);
    });
}

void PlayerPendingCardWidget::applyProgress(int progress, int doneGames, int totalGames)
{
    m_progressBar->setValue(progress);
    m_progressInfoLabel->setText(QString("%1% complete  (%2 games)").arg(progress).arg(totalGames));
    m_gamesLabel->setText(QString("Games: %1    Done: %2").arg(totalGames).arg(doneGames));
}

void PlayerPendingCardWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked(m_username);
    QFrame::mousePressEvent(event);
} 