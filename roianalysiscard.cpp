#include "roianalysiscard.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>

ROIAnalysisCard::ROIAnalysisCard(QWidget *parent)
    : QFrame(parent),
      m_iconLabel(new QLabel("📊", this)),
      m_titleLabel(new QLabel("Análisis Longitudinal (ROI)", this)),
      m_subtitleLabel(new QLabel("Métricas clave del rendimiento del jugador a lo largo del tiempo.", this)),
      m_metricsLayout(new QHBoxLayout()),
      m_roiMedioValue(nullptr),
      m_roiMaximoValue(nullptr),
      m_desviacionValue(nullptr)
{
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Plain);
    setObjectName("roiAnalysisCard");

    // Layout principal
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(12);

    // Encabezado con icono y título
    auto *headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(6);

    m_iconLabel->setFixedSize(18, 18);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setStyleSheet("font-size: 16px; color: #2ECC71;");
    headerLayout->addWidget(m_iconLabel);

    m_titleLabel->setStyleSheet("font-weight: 700; font-size: 16px; color: #FFFFFF;");
    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch();

    mainLayout->addLayout(headerLayout);

    // Subtítulo
    m_subtitleLabel->setStyleSheet("font-size: 12px; color: #9BA5B1;");
    mainLayout->addWidget(m_subtitleLabel);

    // Espacio adicional
    mainLayout->addSpacing(20);

    // Layout horizontal para las métricas
    m_metricsLayout->setSpacing(20);
    m_metricsLayout->setContentsMargins(0, 0, 0, 0);

    // Crear las tres métricas
    auto *roiMedioWidget = createMetricWidget("📈", "ROI Medio", "-188", QColor("#2ECC71"));
    m_roiMedioValue = roiMedioWidget->findChild<QLabel*>("valueLabel");
    m_metricsLayout->addWidget(roiMedioWidget);

    auto *roiMaximoWidget = createMetricWidget("📊", "ROI Máximo", "2514", QColor("#3498DB"));
    m_roiMaximoValue = roiMaximoWidget->findChild<QLabel*>("valueLabel");
    m_metricsLayout->addWidget(roiMaximoWidget);

    auto *desviacionWidget = createMetricWidget("Σ", "Desviación ROI", "3364", QColor("#9B59B6"));
    m_desviacionValue = desviacionWidget->findChild<QLabel*>("valueLabel");
    m_metricsLayout->addWidget(desviacionWidget);

    mainLayout->addLayout(m_metricsLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);

    // Fondo oscuro
    setStyleSheet("#roiAnalysisCard { background-color: #111921; border-radius: 8px; }");
}

QWidget* ROIAnalysisCard::createMetricWidget(const QString &icon, const QString &label, 
                                            const QString &value, const QColor &valueColor)
{
    auto *widget = new QWidget(this);
    auto *layout = new QVBoxLayout(widget);
    layout->setSpacing(8);
    layout->setAlignment(Qt::AlignCenter);

    // Icono
    auto *iconLabel = new QLabel(icon, widget);
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setStyleSheet(QString("font-size: 24px; color: %1;").arg(valueColor.name()));
    layout->addWidget(iconLabel);

    // Etiqueta
    auto *textLabel = new QLabel(label, widget);
    textLabel->setAlignment(Qt::AlignCenter);
    textLabel->setStyleSheet("font-size: 12px; color: #9BA5B1;");
    layout->addWidget(textLabel);

    // Valor
    auto *valueLabel = new QLabel(value, widget);
    valueLabel->setObjectName("valueLabel");
    valueLabel->setAlignment(Qt::AlignCenter);
    valueLabel->setStyleSheet(QString("font-weight: 700; font-size: 32px; color: %1;").arg(valueColor.name()));
    layout->addWidget(valueLabel);

    widget->setLayout(layout);
    return widget;
}

void ROIAnalysisCard::setROIMedio(const QString &value, const QColor &color)
{
    if (m_roiMedioValue) {
        m_roiMedioValue->setText(value);
        m_roiMedioValue->setStyleSheet(QString("font-weight: 700; font-size: 32px; color: %1;").arg(color.name()));
    }
}

void ROIAnalysisCard::setROIMaximo(const QString &value, const QColor &color)
{
    if (m_roiMaximoValue) {
        m_roiMaximoValue->setText(value);
        m_roiMaximoValue->setStyleSheet(QString("font-weight: 700; font-size: 32px; color: %1;").arg(color.name()));
    }
}

void ROIAnalysisCard::setDesviacionROI(const QString &value, const QColor &color)
{
    if (m_desviacionValue) {
        m_desviacionValue->setText(value);
        m_desviacionValue->setStyleSheet(QString("font-weight: 700; font-size: 32px; color: %1;").arg(color.name()));
    }
} 