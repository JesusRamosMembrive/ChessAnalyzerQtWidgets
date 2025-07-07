#pragma once

#include <QFrame>

class QLabel;
class QVBoxLayout;
class QHBoxLayout;

class ClutchPerformanceCard : public QFrame
{
    Q_OBJECT
public:
    explicit ClutchPerformanceCard(QWidget *parent = nullptr);

    // Establece los valores de las métricas
    void setDiferenciaMediaClutch(const QString &value);
    void setPorcentajePartidasClutch(double percentage);

private:
    // Método auxiliar para crear cada métrica
    QWidget* createMetricRow(const QString &name, const QString &value, const QString &tooltip = QString());

private:
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_subtitleLabel;
    QVBoxLayout *m_metricsLayout;
    
    // Labels para los valores
    QLabel *m_diferenciaValue;
    QLabel *m_porcentajeValue;
}; 