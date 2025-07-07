#pragma once

#include <QFrame>

class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QProgressBar;

class TrendsCard : public QFrame
{
    Q_OBJECT
public:
    explicit TrendsCard(QWidget *parent = nullptr);

    // Añade una tendencia con barra de progreso
    void addTrend(const QString &name, const QString &value, int progress, const QString &tooltip = QString());
    
    // Establece el estado de evaluación
    void setEvaluationStatus(const QString &status, const QColor &color = QColor("#FF8C00"));

private:
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_subtitleLabel;
    QVBoxLayout *m_trendsLayout;
    QLabel *m_evaluationLabel;
    QLabel *m_evaluationStatusLabel;
}; 