#include "metricscard.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>

MetricsCard::MetricsCard(QWidget *parent)
    : QFrame(parent),
      m_titleLabel(new QLabel("Métricas de Calidad", this)),
      m_subtitleLabel(new QLabel("Indicadores de la calidad y consistencia del juego.", this)),
      m_metricsLayout(new QVBoxLayout())
{
    // Configuración del frame
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Plain);
    setObjectName("metricsCard");

    // Layout principal
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(6);

    // Título
    m_titleLabel->setStyleSheet("font-weight: 700; font-size: 14px; color: #FFFFFF;");
    mainLayout->addWidget(m_titleLabel);

    // Subtítulo
    m_subtitleLabel->setStyleSheet("font-size: 11px; color: #9BA5B1;");
    mainLayout->addWidget(m_subtitleLabel);

    // Separación sutil debajo del subtítulo
    auto *separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Plain);
    separator->setStyleSheet("color: #2E3740;");
    mainLayout->addWidget(separator);

    // Layout para las métricas
    m_metricsLayout->setSpacing(4);
    mainLayout->addLayout(m_metricsLayout);

    mainLayout->addStretch();

    setLayout(mainLayout);

    // Color de fondo oscuro consistente con otras tarjetas
    setStyleSheet("#metricsCard { background-color: #111921; border-radius: 6px; }");
}

void MetricsCard::addMetric(const QString &name, const QString &value)
{
    auto *rowLayout = new QHBoxLayout();
    rowLayout->setSpacing(4);

    auto *nameLabel = new QLabel(name, this);
    nameLabel->setStyleSheet("font-size: 12px; color: #9BA5B1;");
    rowLayout->addWidget(nameLabel);

    // Espaciador para empujar el valor a la derecha
    rowLayout->addStretch();

    auto *valueLabel = new QLabel(value, this);
    valueLabel->setStyleSheet("font-weight: 600; font-size: 12px; color: #FFFFFF;");
    rowLayout->addWidget(valueLabel);

    m_metricsLayout->addLayout(rowLayout);
} 