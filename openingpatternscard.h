#pragma once

#include <QFrame>

class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QProgressBar;

class OpeningPatternsCard : public QFrame
{
    Q_OBJECT
public:
    explicit OpeningPatternsCard(QWidget *parent = nullptr);

    // Establece los valores de las métricas
    void setDiversidad(double value);
    void setProfundidad(double value);
    void setAmplitud(int value);
    void setTasa2f3(double percentage);

private:
    // Método auxiliar para crear cada métrica con barra de progreso
    QWidget* createMetricWidget(const QString &label, const QString &value, 
                               double progress, const QString &tooltip = QString());

private:
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_subtitleLabel;
    QHBoxLayout *m_metricsLayout;
    
    // Widgets de métricas
    QProgressBar *m_diversidadBar;
    QProgressBar *m_profundidadBar;
    QProgressBar *m_amplitudBar;
    QProgressBar *m_tasaBar;
    
    QLabel *m_diversidadValue;
    QLabel *m_profundidadValue;
    QLabel *m_amplitudValue;
    QLabel *m_tasaValue;
}; 