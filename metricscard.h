#pragma once

#include <QFrame>

class QLabel;
class QVBoxLayout;
class QHBoxLayout;

class MetricsCard : public QFrame
{
    Q_OBJECT
public:
    explicit MetricsCard(QWidget *parent = nullptr);

    // Agrega una nueva métrica a la tarjeta
    void addMetric(const QString &name, const QString &value);

private:
    QLabel *m_titleLabel;
    QLabel *m_subtitleLabel;
    QVBoxLayout *m_metricsLayout;
}; 