#pragma once

#include <QFrame>

class QLabel;
class QHBoxLayout;
class QVBoxLayout;

class ROIAnalysisCard : public QFrame
{
    Q_OBJECT
public:
    explicit ROIAnalysisCard(QWidget *parent = nullptr);

    // Establece los valores de las métricas
    void setROIMedio(const QString &value, const QColor &color = QColor("#2ECC71"));
    void setROIMaximo(const QString &value, const QColor &color = QColor("#3498DB"));
    void setDesviacionROI(const QString &value, const QColor &color = QColor("#9B59B6"));

private:
    // Método auxiliar para crear cada métrica
    QWidget* createMetricWidget(const QString &icon, const QString &label, 
                               const QString &value, const QColor &valueColor);

private:
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_subtitleLabel;
    QHBoxLayout *m_metricsLayout;
    
    // Labels para los valores
    QLabel *m_roiMedioValue;
    QLabel *m_roiMaximoValue;
    QLabel *m_desviacionValue;
}; 