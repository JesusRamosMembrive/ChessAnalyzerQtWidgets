#pragma once

#include <QFrame>

class QLabel;

class CardWidget : public QFrame
{
    Q_OBJECT
public:
    explicit CardWidget(const QString &title = QString(), QWidget *parent = nullptr);

    // Permite actualizar dinámicamente los distintos elementos del card
    void setValue(const QString &value, const QColor &color = Qt::green);
    void setSubtitle(const QString &subtitle);
    void setIcon(const QPixmap &pixmap);

private:
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_valueLabel;
    QLabel *m_subtitleLabel;
}; 