#pragma once

#include <QFrame>
#include <QVector>

class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class SimpleBarChart;
class SimplePieChart;

class GamePhaseQualityCard : public QFrame
{
    Q_OBJECT
public:
    explicit GamePhaseQualityCard(QWidget *parent = nullptr);

    // Establece los valores ACPL por fase
    void setACPLApertura(double value);
    void setACPLMedioJuego(double value);
    void setACPLFinal(double value);
    
    // Establece la distribución de pérdidas por fase
    void setDistribucionPerdidas(double apertura, double medioJuego, double final);
    
    // Establece la tasa de errores graves
    void setTasaErroresGraves(double percentage);

private:
    // Widgets de interfaz
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_subtitleLabel;
    
    // Gráficos personalizados
    SimpleBarChart *m_barChartView;
    SimplePieChart *m_pieChartView;
    SimplePieChart *m_errorChartView;
    
    // Labels de valores
    QLabel *m_aperturaLabel;
    QLabel *m_medioJuegoLabel;
    QLabel *m_finalLabel;
    QLabel *m_tasaErroresLabel;
}; 