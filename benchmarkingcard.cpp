#include "benchmarkingcard.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QProgressBar>

BenchmarkingCard::BenchmarkingCard(QWidget *parent)
    : QFrame(parent),
      m_titleLabel(new QLabel("👥 Benchmarking vs Pares", this)),
      m_subtitleLabel(new QLabel("Comparación con jugadores de ELO similar (±200 puntos)", this)),
      m_comparisonLayout(new QVBoxLayout()),
      m_directComparisonLayout(new QVBoxLayout())
{
    // Configuración del frame
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Plain);
    setObjectName("benchmarkingCard");

    // Layout principal
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(8);

    // Título
    m_titleLabel->setStyleSheet("font-weight: 700; font-size: 16px; color: #FFFFFF;");
    mainLayout->addWidget(m_titleLabel);

    // Subtítulo
    m_subtitleLabel->setStyleSheet("font-size: 12px; color: #9BA5B1;");
    mainLayout->addWidget(m_subtitleLabel);

    // Separador
    auto *separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Plain);
    separator->setStyleSheet("color: #2E3740;");
    mainLayout->addWidget(separator);

    // Espaciado adicional
    mainLayout->addSpacing(12);

    // Sección de comparaciones con barras de progreso
    m_comparisonLayout->setSpacing(20);
    mainLayout->addLayout(m_comparisonLayout);

    // Crear las comparaciones iniciales
    // ACPL
    setupComparisonWidget(m_comparisonLayout, 
                         "Calidad de Juego (ACPL)", 
                         90,
                         "Peor",
                         "Muy Alto (Top 10%)",
                         "Mejor",
                         "Su ACPL está en el top 10% - excepcionalmente bajo para su nivel. Esto puede ser sospechoso.");

    // Diversidad de Aperturas
    setupComparisonWidget(m_comparisonLayout,
                         "Diversidad de Aperturas",
                         5,
                         "Menos Diverso",
                         "Bajo (Bottom 25%)",
                         "Más Diverso", 
                         "Tiende a jugar un repertorio más limitado de aperturas, lo cual puede ser una estrategia válida.");

    // Espaciado antes de la sección de comparación directa
    mainLayout->addSpacing(16);

    // Título de comparación directa
    auto *directComparisonTitle = new QLabel("Comparación Directa con Pares", this);
    directComparisonTitle->setStyleSheet("font-weight: 600; font-size: 14px; color: #FFFFFF;");
    mainLayout->addWidget(directComparisonTitle);

    // Separador para comparación directa
    auto *separator2 = new QFrame(this);
    separator2->setFrameShape(QFrame::HLine);
    separator2->setFrameShadow(QFrame::Plain);
    separator2->setStyleSheet("color: #2E3740;");
    mainLayout->addWidget(separator2);

    mainLayout->addSpacing(8);

    // Layout para comparaciones directas
    m_directComparisonLayout->setSpacing(8);
    
    // ACPL Difference
    auto *acplDiffLayout = new QHBoxLayout();
    auto *acplDiffLabel = new QLabel("Diferencia en ACPL vs Pares", this);
    acplDiffLabel->setStyleSheet("font-size: 12px; color: #9BA5B1;");
    acplDiffLayout->addWidget(acplDiffLabel);
    
    auto *acplDiffHelpIcon = new QLabel(" ⓘ", this);
    acplDiffHelpIcon->setStyleSheet("font-size: 12px; color: #6B7684;");
    acplDiffHelpIcon->setToolTip("La diferencia en pérdida de centipawn promedio comparada con jugadores similares");
    acplDiffLayout->addWidget(acplDiffHelpIcon);
    
    acplDiffLayout->addStretch();
    
    m_directACPLLabel = new QLabel("0.00 (mejor)", this);
    m_directACPLLabel->setStyleSheet("font-weight: 600; font-size: 12px; color: #FFFFFF;");
    acplDiffLayout->addWidget(m_directACPLLabel);
    
    m_directComparisonLayout->addLayout(acplDiffLayout);

    // Coincidence Difference
    auto *coincidenceDiffLayout = new QHBoxLayout();
    auto *coincidenceDiffLabel = new QLabel("Diferencia en Coincidencia vs Pares", this);
    coincidenceDiffLabel->setStyleSheet("font-size: 12px; color: #9BA5B1;");
    coincidenceDiffLayout->addWidget(coincidenceDiffLabel);
    
    auto *coincidenceDiffHelpIcon = new QLabel(" ⓘ", this);
    coincidenceDiffHelpIcon->setStyleSheet("font-size: 12px; color: #6B7684;");
    coincidenceDiffHelpIcon->setToolTip("La diferencia en el porcentaje de movimientos que coinciden con el motor comparada con jugadores similares");
    coincidenceDiffLayout->addWidget(coincidenceDiffHelpIcon);
    
    coincidenceDiffLayout->addStretch();
    
    m_directCoincidenceLabel = new QLabel("0.00% (menor)", this);
    m_directCoincidenceLabel->setStyleSheet("font-weight: 600; font-size: 12px; color: #FFFFFF;");
    coincidenceDiffLayout->addWidget(m_directCoincidenceLabel);
    
    m_directComparisonLayout->addLayout(coincidenceDiffLayout);

    mainLayout->addLayout(m_directComparisonLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);

    // Color de fondo oscuro
    setStyleSheet("#benchmarkingCard { background-color: #111921; border-radius: 8px; }");
}

void BenchmarkingCard::setupComparisonWidget(QVBoxLayout *parentLayout,
                                            const QString &metricName,
                                            int percentile,
                                            const QString &leftLabel,
                                            const QString &assessment,
                                            const QString &rightLabel,
                                            const QString &interpretation)
{
    auto *metricContainer = new QWidget(this);
    auto *metricLayout = new QVBoxLayout(metricContainer);
    metricLayout->setContentsMargins(0, 0, 0, 0);
    metricLayout->setSpacing(6);

    // Título de la métrica con percentil
    auto *metricHeaderLayout = new QHBoxLayout();
    
    auto *metricLabel = new QLabel(metricName, this);
    metricLabel->setStyleSheet("font-weight: 600; font-size: 13px; color: #FFFFFF;");
    metricHeaderLayout->addWidget(metricLabel);
    
    metricHeaderLayout->addStretch();
    
    auto *percentileLabel = new QLabel(QString("Percentil %1").arg(percentile), this);
    percentileLabel->setStyleSheet("font-weight: 700; font-size: 14px; color: #4FC3F7;");
    metricHeaderLayout->addWidget(percentileLabel);
    
    metricLayout->addLayout(metricHeaderLayout);

    // Barra de progreso personalizada
    auto *progressBar = new QProgressBar(this);
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
    progressBar->setValue(percentile);
    progressBar->setTextVisible(false);
    progressBar->setFixedHeight(8);
    
    // Estilo de la barra de progreso
    QString progressStyle = QString(
        "QProgressBar {"
        "    background-color: #2E3740;"
        "    border-radius: 4px;"
        "}"
        "QProgressBar::chunk {"
        "    background-color: %1;"
        "    border-radius: 4px;"
        "}"
    ).arg(percentile >= 75 ? "#4FC3F7" : (percentile >= 25 ? "#FFB74D" : "#E57373"));
    
    progressBar->setStyleSheet(progressStyle);
    metricLayout->addWidget(progressBar);

    // Etiquetas debajo de la barra
    auto *labelsLayout = new QHBoxLayout();
    labelsLayout->setContentsMargins(0, 0, 0, 0);
    
    auto *leftMetricLabel = new QLabel(leftLabel, this);
    leftMetricLabel->setStyleSheet("font-size: 11px; color: #6B7684;");
    labelsLayout->addWidget(leftMetricLabel);
    
    auto *assessmentLabel = new QLabel(assessment, this);
    assessmentLabel->setStyleSheet("font-weight: 600; font-size: 11px; color: #FFFFFF;");
    assessmentLabel->setAlignment(Qt::AlignCenter);
    labelsLayout->addWidget(assessmentLabel, 1);
    
    auto *rightMetricLabel = new QLabel(rightLabel, this);
    rightMetricLabel->setStyleSheet("font-size: 11px; color: #6B7684;");
    rightMetricLabel->setAlignment(Qt::AlignRight);
    labelsLayout->addWidget(rightMetricLabel);
    
    metricLayout->addLayout(labelsLayout);

    // Interpretación
    auto *interpretationLabel = new QLabel(interpretation, this);
    interpretationLabel->setStyleSheet("font-size: 11px; color: #9BA5B1; margin-top: 4px;");
    interpretationLabel->setWordWrap(true);
    
    auto *interpretationLayout = new QHBoxLayout();
    auto *interpretationPrefix = new QLabel("Interpretación:", this);
    interpretationPrefix->setStyleSheet("font-weight: 600; font-size: 11px; color: #9BA5B1;");
    interpretationLayout->addWidget(interpretationPrefix);
    interpretationLayout->addWidget(interpretationLabel, 1);
    
    metricLayout->addLayout(interpretationLayout);

    parentLayout->addWidget(metricContainer);

    // Guardar referencias si es necesario para actualizaciones posteriores
    if (metricName.contains("ACPL")) {
        m_acplProgressBar = progressBar;
        m_acplAssessmentLabel = assessmentLabel;
        m_acplInterpretationLabel = interpretationLabel;
    } else if (metricName.contains("Diversidad")) {
        m_diversityProgressBar = progressBar;
        m_diversityAssessmentLabel = assessmentLabel;
        m_diversityInterpretationLabel = interpretationLabel;
    }
}

void BenchmarkingCard::setACPLComparison(int percentile, const QString &assessment)
{
    if (m_acplProgressBar) {
        m_acplProgressBar->setValue(percentile);
        
        // Actualizar color según el percentil
        QString color = percentile >= 75 ? "#4FC3F7" : (percentile >= 25 ? "#FFB74D" : "#E57373");
        m_acplProgressBar->setStyleSheet(QString(
            "QProgressBar {"
            "    background-color: #2E3740;"
            "    border-radius: 4px;"
            "}"
            "QProgressBar::chunk {"
            "    background-color: %1;"
            "    border-radius: 4px;"
            "}"
        ).arg(color));
    }
    
    if (m_acplAssessmentLabel) {
        m_acplAssessmentLabel->setText(assessment);
    }
}

void BenchmarkingCard::setOpeningDiversityComparison(int percentile, const QString &assessment)
{
    if (m_diversityProgressBar) {
        m_diversityProgressBar->setValue(percentile);
        
        // Actualizar color según el percentil
        QString color = percentile >= 75 ? "#4FC3F7" : (percentile >= 25 ? "#FFB74D" : "#E57373");
        m_diversityProgressBar->setStyleSheet(QString(
            "QProgressBar {"
            "    background-color: #2E3740;"
            "    border-radius: 4px;"
            "}"
            "QProgressBar::chunk {"
            "    background-color: %1;"
            "    border-radius: 4px;"
            "}"
        ).arg(color));
    }
    
    if (m_diversityAssessmentLabel) {
        m_diversityAssessmentLabel->setText(assessment);
    }
}

void BenchmarkingCard::setDirectComparisonACPL(double difference)
{
    if (m_directACPLLabel) {
        QString status = difference <= 0 ? "(mejor)" : "(peor)";
        m_directACPLLabel->setText(QString("%1 %2").arg(difference, 0, 'f', 2).arg(status));
        
        // Color según si es mejor o peor
        QString color = difference <= 0 ? "#4FC3F7" : "#E57373";
        m_directACPLLabel->setStyleSheet(QString("font-weight: 600; font-size: 12px; color: %1;").arg(color));
    }
}

void BenchmarkingCard::setDirectComparisonCoincidence(double difference)
{
    if (m_directCoincidenceLabel) {
        QString status = difference <= 0 ? "(menor)" : "(mayor)";
        m_directCoincidenceLabel->setText(QString("%1% %2").arg(difference, 0, 'f', 2).arg(status));
        
        // Color según si es menor o mayor
        QString color = difference <= 0 ? "#4FC3F7" : "#E57373";
        m_directCoincidenceLabel->setStyleSheet(QString("font-weight: 600; font-size: 12px; color: %1;").arg(color));
    }
} 