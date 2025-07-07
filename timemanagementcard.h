#pragma once

#include <QFrame>

class QLabel;
class QVBoxLayout;
class QHBoxLayout;

class TimeManagementCard : public QFrame
{
    Q_OBJECT
public:
    explicit TimeManagementCard(QWidget *parent = nullptr);

    // Establece los valores de las métricas
    void setTiempoMedioPorJugada(const QString &value);
    void setVarianzaTiempo(const QString &value);
    void setPuntuacionUniformidad(double value);
    void setPicosLag(int value);

private:
    // Método auxiliar para crear cada métrica
    QWidget* createMetricRow(const QString &name, const QString &value, const QString &tooltip = QString());

private:
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_subtitleLabel;
    QVBoxLayout *m_metricsLayout;
    
    // Labels para los valores
    QLabel *m_tiempoMedioValue;
    QLabel *m_varianzaValue;
    QLabel *m_puntuacionValue;
    QLabel *m_picosValue;
}; 