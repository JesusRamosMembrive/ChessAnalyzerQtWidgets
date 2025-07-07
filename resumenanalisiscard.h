#pragma once

#include <QFrame>

class QLabel;
class QVBoxLayout;
class QHBoxLayout;

class ResumenAnalisisCard : public QFrame
{
    Q_OBJECT
public:
    explicit ResumenAnalisisCard(QWidget *parent = nullptr);

    // Establece los valores de las métricas principales
    void setPuntuacionRiesgoFinal(const QString &value, const QColor &color = QColor("#2ECC71"));
    void setPartidasAnalizadas(const QString &value, const QColor &color = QColor("#3498DB"));
    void setPartidasSospechosas(const QString &value, const QColor &color = QColor("#9B59B6"));
    
    // Establece la conclusión del análisis
    void setConclusion(const QString &conclusion);

private:
    // Método auxiliar para crear cada métrica
    QWidget* createMetricWidget(const QString &label, const QString &value, const QColor &valueColor);

private:
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_subtitleLabel;
    QHBoxLayout *m_metricsLayout;
    QLabel *m_conclusionLabel;
    
    // Labels para los valores de las métricas
    QLabel *m_puntuacionRiesgoValue;
    QLabel *m_partidasAnalizadasValue;
    QLabel *m_partidasSospechosasValue;
}; 