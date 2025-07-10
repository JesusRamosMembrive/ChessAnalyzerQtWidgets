#include "connectionerrorwidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

ConnectionErrorWidget::ConnectionErrorWidget(QWidget *parent)
    : QFrame(parent),
      m_iconLabel(nullptr),
      m_titleLabel(nullptr),
      m_descLabel(nullptr),
      m_detailsLabel(nullptr),
      m_retryButton(nullptr)
{
    setObjectName("connectionErrorWidget");
    setStyleSheet("#connectionErrorWidget { background-color: #1B262F; border-radius: 12px; }");

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setSpacing(12);

    // Icono ⚠
    m_iconLabel = new QLabel("⚠", this);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setStyleSheet("font-size: 32px; color: #E74C3C;");
    mainLayout->addWidget(m_iconLabel);

    // Título
    m_titleLabel = new QLabel(tr("Connection Error"), this);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("font-weight: 700; font-size: 20px; color: #E74C3C;");
    mainLayout->addWidget(m_titleLabel);

    // Descripción corta
    m_descLabel = new QLabel(tr("Request timed out - backend may be slow or unavailable"), this);
    m_descLabel->setWordWrap(true);
    m_descLabel->setAlignment(Qt::AlignCenter);
    m_descLabel->setStyleSheet("font-size: 13px; color: #BDC3C7;");
    mainLayout->addWidget(m_descLabel);

    // Detalles
    m_detailsLabel = new QLabel(tr("This usually means:\n• The backend server is not running\n• The server URL has changed\n• Network connectivity issues"), this);
    m_detailsLabel->setAlignment(Qt::AlignLeft);
    m_detailsLabel->setWordWrap(true);
    m_detailsLabel->setStyleSheet("font-size: 12px; color: #9BA5B1;");
    mainLayout->addWidget(m_detailsLabel);

    // Botón Try Again
    m_retryButton = new QPushButton(tr("Try Again"), this);
    m_retryButton->setFixedWidth(120);
    m_retryButton->setStyleSheet(R"(
        QPushButton {
            background-color: #3498DB;
            color: #FFFFFF;
            border: none;
            border-radius: 6px;
            padding: 8px 16px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #5DADE2;
        }
        QPushButton:pressed {
            background-color: #2E86C1;
        }
    )");
    connect(m_retryButton, &QPushButton::clicked, this, &ConnectionErrorWidget::onRetry, Qt::QueuedConnection);
    mainLayout->addWidget(m_retryButton, 0, Qt::AlignCenter);

    setLayout(mainLayout);
}

void ConnectionErrorWidget::onRetry()
{
    emit retryClicked();
} 