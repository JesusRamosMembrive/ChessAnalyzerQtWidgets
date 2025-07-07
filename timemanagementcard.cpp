#include "timemanagementcard.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>

TimeManagementCard::TimeManagementCard(QWidget *parent)
    : QFrame(parent),
      m_iconLabel(new QLabel("⏱", this)),
      m_titleLabel(new QLabel("Gestión del Tiempo", this)),
      m_subtitleLabel(new QLabel("Análisis de los patrones de uso del tiempo.", this)),
      m_metricsLayout(new QVBoxLayout()),
      m_tiempoMedioValue(nullptr),
      m_varianzaValue(nullptr),
      m_puntuacionValue(nullptr),
      m_picosValue(nullptr)
{
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Plain);
    setObjectName("timeManagementCard");

    // Layout principal
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(10);

    // Encabezado con icono y título
    auto *headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(6);

    m_iconLabel->setFixedSize(18, 18);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setStyleSheet("font-size: 16px; color: #3498DB;");
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
    auto *tiempoMedioWidget = createMetricRow("Tiempo Medio por Jugada", "46.09s");
    m_tiempoMedioValue = tiempoMedioWidget->findChild<QLabel*>("valueLabel");
    m_metricsLayout->addWidget(tiempoMedioWidget);
    
    auto *varianzaWidget = createMetricRow("Varianza del Tiempo", "110641.59");
    m_varianzaValue = varianzaWidget->findChild<QLabel*>("valueLabel");
    m_metricsLayout->addWidget(varianzaWidget);
    
    auto *puntuacionWidget = createMetricRow("Puntuación de Uniformidad", "-8.22");
    m_puntuacionValue = puntuacionWidget->findChild<QLabel*>("valueLabel");
    m_metricsLayout->addWidget(puntuacionWidget);
    
    auto *picosWidget = createMetricRow("Picos de Lag", "91");
    m_picosValue = picosWidget->findChild<QLabel*>("valueLabel");
    m_metricsLayout->addWidget(picosWidget);

    mainLayout->addLayout(m_metricsLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);

    // Fondo oscuro
    setStyleSheet("#timeManagementCard { background-color: #111921; border-radius: 8px; }");
}

QWidget* TimeManagementCard::createMetricRow(const QString &name, const QString &value, const QString &tooltip)
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

void TimeManagementCard::setTiempoMedioPorJugada(const QString &value)
{
    if (m_tiempoMedioValue) {
        m_tiempoMedioValue->setText(value);
    }
}

void TimeManagementCard::setVarianzaTiempo(const QString &value)
{
    if (m_varianzaValue) {
        m_varianzaValue->setText(value);
    }
}

void TimeManagementCard::setPuntuacionUniformidad(double value)
{
    if (m_puntuacionValue) {
        m_puntuacionValue->setText(QString::number(value, 'f', 2));
    }
}

void TimeManagementCard::setPicosLag(int value)
{
    if (m_picosValue) {
        m_picosValue->setText(QString::number(value));
    }
} 