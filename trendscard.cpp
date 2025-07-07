#include "trendscard.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QProgressBar>

TrendsCard::TrendsCard(QWidget *parent)
    : QFrame(parent),
      m_iconLabel(new QLabel("📈", this)),
      m_titleLabel(new QLabel("Tendencias", this)),
      m_subtitleLabel(new QLabel("Análisis de tendencias temporales.", this)),
      m_trendsLayout(new QVBoxLayout()),
      m_evaluationLabel(new QLabel("Evaluación de Tendencia", this)),
      m_evaluationStatusLabel(new QLabel(this))
{
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Plain);
    setObjectName("trendsCard");

    // Layout principal
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(8);

    // Encabezado con icono y título
    auto *headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(6);

    m_iconLabel->setFixedSize(16, 16);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setStyleSheet("font-size: 14px;");
    headerLayout->addWidget(m_iconLabel);

    m_titleLabel->setStyleSheet("font-weight: 700; font-size: 14px; color: #FFFFFF;");
    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch();

    mainLayout->addLayout(headerLayout);

    // Subtítulo
    m_subtitleLabel->setStyleSheet("font-size: 11px; color: #9BA5B1;");
    mainLayout->addWidget(m_subtitleLabel);

    // Separador
    auto *separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Plain);
    separator->setStyleSheet("color: #2E3740;");
    mainLayout->addWidget(separator);

    // Layout de tendencias
    m_trendsLayout->setSpacing(12);
    mainLayout->addLayout(m_trendsLayout);

    // Sección de evaluación
    mainLayout->addSpacing(8);
    
    m_evaluationLabel->setStyleSheet("font-size: 12px; color: #9BA5B1; text-align: center;");
    m_evaluationLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_evaluationLabel);

    m_evaluationStatusLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_evaluationStatusLabel);

    mainLayout->addStretch();

    setLayout(mainLayout);

    // Fondo oscuro
    setStyleSheet("#trendsCard { background-color: #111921; border-radius: 6px; }");
}

void TrendsCard::addTrend(const QString &name, const QString &value, int progress, const QString &tooltip)
{
    // Contenedor para cada tendencia
    auto *trendWidget = new QWidget(this);
    auto *trendLayout = new QVBoxLayout(trendWidget);
    trendLayout->setSpacing(4);
    trendLayout->setContentsMargins(0, 0, 0, 0);

    // Nombre y valor
    auto *headerLayout = new QHBoxLayout();
    
    auto *nameLabel = new QLabel(name, this);
    nameLabel->setStyleSheet("font-size: 12px; color: #9BA5B1;");
    if (!tooltip.isEmpty()) {
        nameLabel->setToolTip(tooltip);
    }
    headerLayout->addWidget(nameLabel);

    headerLayout->addStretch();

    auto *valueLabel = new QLabel(value, this);
    valueLabel->setStyleSheet("font-weight: 600; font-size: 12px; color: #FFFFFF;");
    headerLayout->addWidget(valueLabel);

    trendLayout->addLayout(headerLayout);

    // Barra de progreso personalizada
    auto *progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(progress);
    progressBar->setTextVisible(false);
    progressBar->setFixedHeight(6);
    
    // Estilo de la barra de progreso
    QString progressStyle = R"(
        QProgressBar {
            background-color: #2E3740;
            border-radius: 3px;
        }
        QProgressBar::chunk {
            background-color: #3498DB;
            border-radius: 3px;
        }
    )";
    progressBar->setStyleSheet(progressStyle);

    trendLayout->addWidget(progressBar);

    // Texto descriptivo opcional
    if (name.contains("ACPL")) {
        auto *descLabel = new QLabel("Mejora significativa", this);
        descLabel->setStyleSheet("font-size: 10px; color: #3498DB;");
        trendLayout->addWidget(descLabel);
    } else if (name.contains("Match Rate")) {
        auto *descLabel = new QLabel("Estable", this);
        descLabel->setStyleSheet("font-size: 10px; color: #9BA5B1;");
        trendLayout->addWidget(descLabel);
    }

    m_trendsLayout->addWidget(trendWidget);
}

void TrendsCard::setEvaluationStatus(const QString &status, const QColor &color)
{
    // Icono y texto del estado
    QString iconText = "📊 ";
    m_evaluationStatusLabel->setText(iconText + status);
    
    QString statusStyle = QString("font-weight: 600; font-size: 14px; color: %1;").arg(color.name());
    m_evaluationStatusLabel->setStyleSheet(statusStyle);
} 