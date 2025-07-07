#include "clutchperformancecard.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>

ClutchPerformanceCard::ClutchPerformanceCard(QWidget *parent)
    : QFrame(parent),
      m_iconLabel(new QLabel("🎯", this)),
      m_titleLabel(new QLabel("Precisión Bajo Presión (Clutch)", this)),
      m_subtitleLabel(new QLabel("Rendimiento en momentos críticos de la partida.", this)),
      m_metricsLayout(new QVBoxLayout()),
      m_diferenciaValue(nullptr),
      m_porcentajeValue(nullptr)
{
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Plain);
    setObjectName("clutchPerformanceCard");

    // Layout principal
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(10);

    // Encabezado con icono y título
    auto *headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(6);

    m_iconLabel->setFixedSize(18, 18);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setStyleSheet("font-size: 16px; color: #E74C3C;");
    headerLayout->addWidget(m_iconLabel);

    m_titleLabel->setStyleSheet("font-weight: 700; font-size: 16px; color: #FFFFFF;");
    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch();

    mainLayout->addLayout(headerLayout);

    // Subtítulo
    m_subtitleLabel->setStyleSheet("font-size: 12px; color: #9BA5B1;");
    mainLayout->addWidget(m_subtitleLabel);

    // Separador
    auto *separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Plain);
    separator->setStyleSheet("color: #2E3740;");
    mainLayout->addWidget(separator);

    // Layout de métricas
    m_metricsLayout->setSpacing(8);
    
    // Crear las métricas
    auto *diferenciaWidget = createMetricRow("Diferencia Media en 'Clutch'", "9361.70");
    m_diferenciaValue = diferenciaWidget->findChild<QLabel*>("valueLabel");
    m_metricsLayout->addWidget(diferenciaWidget);
    
    auto *porcentajeWidget = createMetricRow("Porcentaje de Partidas 'Clutch'", "10.20%");
    m_porcentajeValue = porcentajeWidget->findChild<QLabel*>("valueLabel");
    m_metricsLayout->addWidget(porcentajeWidget);

    mainLayout->addLayout(m_metricsLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);

    // Fondo oscuro
    setStyleSheet("#clutchPerformanceCard { background-color: #111921; border-radius: 8px; }");
}

QWidget* ClutchPerformanceCard::createMetricRow(const QString &name, const QString &value, const QString &tooltip)
{
    auto *widget = new QWidget(this);
    auto *layout = new QHBoxLayout(widget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(4);

    auto *nameLabel = new QLabel(name, widget);
    nameLabel->setStyleSheet("font-size: 13px; color: #9BA5B1;");
    if (!tooltip.isEmpty()) {
        nameLabel->setToolTip(tooltip);
    }
    layout->addWidget(nameLabel);

    layout->addStretch();

    auto *valueLabel = new QLabel(value, widget);
    valueLabel->setObjectName("valueLabel");
    valueLabel->setStyleSheet("font-weight: 600; font-size: 13px; color: #FFFFFF;");
    layout->addWidget(valueLabel);

    widget->setLayout(layout);
    return widget;
}

void ClutchPerformanceCard::setDiferenciaMediaClutch(const QString &value)
{
    if (m_diferenciaValue) {
        m_diferenciaValue->setText(value);
    }
}

void ClutchPerformanceCard::setPorcentajePartidasClutch(double percentage)
{
    if (m_porcentajeValue) {
        m_porcentajeValue->setText(QString::number(percentage, 'f', 2) + "%");
    }
} 