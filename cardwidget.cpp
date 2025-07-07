#include "cardwidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QFrame>
#include <QHBoxLayout>
#include <QPainter>

CardWidget::CardWidget(const QString &title, QWidget *parent)
    : QFrame(parent),
      m_iconLabel(new QLabel(this)),
      m_titleLabel(new QLabel(title, this)),
      m_valueLabel(new QLabel(QString(), this)),
      m_subtitleLabel(new QLabel(QString(), this))
{
    // Configuramos el estilo base del frame
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Plain);
    setObjectName("cardWidget");

    // Layout principal
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(12, 12, 12, 12);

    // Icono y título en la misma línea
    auto *headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(6);

    m_iconLabel->setFixedSize(16, 16);
    headerLayout->addWidget(m_iconLabel);

    m_titleLabel->setStyleSheet("font-weight: 600; font-size: 12px; color: #9BA5B1;");
    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch();

    mainLayout->addLayout(headerLayout);

    // Valor principal (número grande)
    m_valueLabel->setStyleSheet("font-weight: 700; font-size: 28px; color: #2ECC71;");
    mainLayout->addWidget(m_valueLabel);

    // Subtítulo (rango de fechas, descripción, etc.)
    m_subtitleLabel->setStyleSheet("font-size: 11px; color: #9BA5B1;");
    mainLayout->addWidget(m_subtitleLabel);

    mainLayout->addStretch();

    setLayout(mainLayout);

    // Color de fondo oscuro por defecto para que resalte el verde
    setStyleSheet("#cardWidget { background-color: #111921; border-radius: 6px; }");
}

void CardWidget::setValue(const QString &value, const QColor &color)
{
    m_valueLabel->setText(value);

    // Actualizamos el color si se proporciona uno distinto
    const QString css = QString("font-weight: 700; font-size: 28px; color: %1;").arg(color.name());
    m_valueLabel->setStyleSheet(css);
}

void CardWidget::setSubtitle(const QString &subtitle)
{
    m_subtitleLabel->setText(subtitle);
}

void CardWidget::setIcon(const QPixmap &pixmap)
{
    if (!pixmap.isNull()) {
        m_iconLabel->setPixmap(pixmap.scaled(m_iconLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
} 