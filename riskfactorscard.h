#pragma once

#include <QFrame>

class QLabel;
class QVBoxLayout;
class QHBoxLayout;

class RiskFactorsCard : public QFrame
{
    Q_OBJECT
public:
    explicit RiskFactorsCard(QWidget *parent = nullptr);

    // Añade un factor con un valor de texto y color opcional
    void addFactor(const QString &name, const QString &value, const QColor &valueColor = Qt::white, const QString &tooltip = QString(), bool addSeparator = false);

private:
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_subtitleLabel;
    QVBoxLayout *m_factorsLayout;
}; 