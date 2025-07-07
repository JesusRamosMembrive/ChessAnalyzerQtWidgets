#pragma once

#include <QFrame>

class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QProgressBar;

class BenchmarkingCard : public QFrame
{
    Q_OBJECT
public:
    explicit BenchmarkingCard(QWidget *parent = nullptr);

    // Actualizar las métricas de comparación
    void setACPLComparison(int percentile, const QString &assessment);
    void setOpeningDiversityComparison(int percentile, const QString &assessment);
    void setDirectComparisonACPL(double difference);
    void setDirectComparisonCoincidence(double difference);

private:
    void setupComparisonWidget(QVBoxLayout *parentLayout, 
                              const QString &metricName, 
                              int percentile,
                              const QString &leftLabel,
                              const QString &assessment,
                              const QString &rightLabel,
                              const QString &interpretation);

    QLabel *m_titleLabel;
    QLabel *m_subtitleLabel;
    
    // Widgets para las comparaciones
    QVBoxLayout *m_comparisonLayout;
    QVBoxLayout *m_directComparisonLayout;
    
    // Para actualizar las visualizaciones
    QProgressBar *m_acplProgressBar;
    QProgressBar *m_diversityProgressBar;
    QLabel *m_acplAssessmentLabel;
    QLabel *m_diversityAssessmentLabel;
    QLabel *m_acplInterpretationLabel;
    QLabel *m_diversityInterpretationLabel;
    QLabel *m_directACPLLabel;
    QLabel *m_directCoincidenceLabel;
}; 