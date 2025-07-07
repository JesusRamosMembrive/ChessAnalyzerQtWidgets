#include "resumenanalisiscard.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>

ResumenAnalisisCard::ResumenAnalisisCard(QWidget *parent)
    : QFrame(parent),
      m_iconLabel(new QLabel("🛡", this)),
      m_titleLabel(new QLabel("Resumen del Análisis", this)),
      m_subtitleLabel(new QLabel("Evaluación integral basada en todas las métricas analizadas.", this)),
      m_metricsLayout(new QHBoxLayout()),
      m_conclusionLabel(new QLabel(this)),
      m_puntuacionRiesgoValue(nullptr),
      m_partidasAnalizadasValue(nullptr),
      m_partidasSospechosasValue(nullptr)
{
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Plain);
    setObjectName("resumenAnalisisCard");

    // Layout principal
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(16);

    // Encabezado con icono y título
    auto *headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(8);

    m_iconLabel->setFixedSize(20, 20);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setStyleSheet("font-size: 18px; color: #2ECC71;");
    headerLayout->addWidget(m_iconLabel);

    m_titleLabel->setStyleSheet("font-weight: 700; font-size: 18px; color: #FFFFFF;");
    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch();

    mainLayout->addLayout(headerLayout);

    // Subtítulo
    m_subtitleLabel->setStyleSheet("font-size: 14px; color: #9BA5B1; margin-bottom: 8px;");
    mainLayout->addWidget(m_subtitleLabel);

    // Espacio adicional
    mainLayout->addSpacing(10);

    // Layout horizontal para las métricas principales
    m_metricsLayout->setSpacing(20);
    m_metricsLayout->setContentsMargins(0, 0, 0, 0);

    // Crear las tres métricas principales
    auto *puntuacionWidget = createMetricWidget("Puntuación de Riesgo Final", "20/100", QColor("#2ECC71"));
    m_puntuacionRiesgoValue = puntuacionWidget->findChild<QLabel*>("valueLabel");
    m_metricsLayout->addWidget(puntuacionWidget);

    auto *partidasWidget = createMetricWidget("Partidas Analizadas", "98", QColor("#3498DB"));
    m_partidasAnalizadasValue = partidasWidget->findChild<QLabel*>("valueLabel");
    m_metricsLayout->addWidget(partidasWidget);

    auto *sospechosasWidget = createMetricWidget("Partidas Sospechosas", "0", QColor("#9B59B6"));
    m_partidasSospechosasValue = sospechosasWidget->findChild<QLabel*>("valueLabel");
    m_metricsLayout->addWidget(sospechosasWidget);

    mainLayout->addLayout(m_metricsLayout);

    // Espacio antes de la conclusión
    mainLayout->addSpacing(20);

    // Separador
    auto *separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Plain);
    separator->setStyleSheet("color: #2E3740; margin: 8px 0px;");
    mainLayout->addWidget(separator);

    // Conclusión
    m_conclusionLabel->setStyleSheet("font-size: 14px; color: #FFFFFF; background-color: #1A2332; "
                                    "padding: 12px; border-radius: 6px; line-height: 1.4;");
    m_conclusionLabel->setWordWrap(true);
    m_conclusionLabel->setText("Conclusión: El análisis indica un riesgo MUY BAJO. Los patrones de juego son consistentes con comportamiento humano natural.");
    mainLayout->addWidget(m_conclusionLabel);

    mainLayout->addStretch();

    setLayout(mainLayout);

    // Fondo oscuro consistente con otras tarjetas
    setStyleSheet("#resumenAnalisisCard { background-color: #111921; border-radius: 8px; }");
}

QWidget* ResumenAnalisisCard::createMetricWidget(const QString &label, const QString &value, const QColor &valueColor)
{
    auto *widget = new QWidget(this);
    auto *layout = new QVBoxLayout(widget);
    layout->setSpacing(8);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(8, 8, 8, 8);

    // Valor principal (número grande)
    auto *valueLabel = new QLabel(value, widget);
    valueLabel->setObjectName("valueLabel");
    valueLabel->setAlignment(Qt::AlignCenter);
    valueLabel->setStyleSheet(QString("font-weight: 700; font-size: 36px; color: %1;").arg(valueColor.name()));
    layout->addWidget(valueLabel);

    // Etiqueta descriptiva
    auto *textLabel = new QLabel(label, widget);
    textLabel->setAlignment(Qt::AlignCenter);
    textLabel->setStyleSheet("font-size: 12px; color: #9BA5B1; font-weight: 500;");
    textLabel->setWordWrap(true);
    layout->addWidget(textLabel);

    widget->setLayout(layout);
    return widget;
}

void ResumenAnalisisCard::setPuntuacionRiesgoFinal(const QString &value, const QColor &color)
{
    if (m_puntuacionRiesgoValue) {
        m_puntuacionRiesgoValue->setText(value);
        m_puntuacionRiesgoValue->setStyleSheet(QString("font-weight: 700; font-size: 36px; color: %1;").arg(color.name()));
    }
}

void ResumenAnalisisCard::setPartidasAnalizadas(const QString &value, const QColor &color)
{
    if (m_partidasAnalizadasValue) {
        m_partidasAnalizadasValue->setText(value);
        m_partidasAnalizadasValue->setStyleSheet(QString("font-weight: 700; font-size: 36px; color: %1;").arg(color.name()));
    }
}

void ResumenAnalisisCard::setPartidasSospechosas(const QString &value, const QColor &color)
{
    if (m_partidasSospechosasValue) {
        m_partidasSospechosasValue->setText(value);
        m_partidasSospechosasValue->setStyleSheet(QString("font-weight: 700; font-size: 36px; color: %1;").arg(color.name()));
    }
}

void ResumenAnalisisCard::setConclusion(const QString &conclusion)
{
    m_conclusionLabel->setText(QString("Conclusión: %1").arg(conclusion));
} 