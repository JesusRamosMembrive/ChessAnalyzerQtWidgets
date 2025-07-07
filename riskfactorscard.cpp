#include "riskfactorscard.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>

RiskFactorsCard::RiskFactorsCard(QWidget *parent)
    : QFrame(parent),
      m_iconLabel(new QLabel("\u26E8", this)),  // Unicode para escudo (🛡)
      m_titleLabel(new QLabel("Factores de Riesgo", this)),
      m_subtitleLabel(new QLabel("Factores específicos que contribuyen a la puntuación de riesgo.", this)),
      m_factorsLayout(new QVBoxLayout())
{
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Plain);
    setObjectName("riskFactorsCard");

    // Layout principal
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(6);

    // Encabezado con icono y título
    auto *headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(6);

    m_iconLabel->setFixedSize(16, 16);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setStyleSheet("font-size: 14px; color: #FF6666;");
    headerLayout->addWidget(m_iconLabel);

    m_titleLabel->setStyleSheet("font-weight: 700; font-size: 14px; color: #FFFFFF;");
    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch();

    mainLayout->addLayout(headerLayout);

    // Subtítulo
    m_subtitleLabel->setStyleSheet("font-size: 11px; color: #9BA5B1;");
    mainLayout->addWidget(m_subtitleLabel);

    // Separador sutil
    auto *separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Plain);
    separator->setStyleSheet("color: #2E3740;");
    mainLayout->addWidget(separator);

    // Layout de factores
    m_factorsLayout->setSpacing(4);
    mainLayout->addLayout(m_factorsLayout);

    mainLayout->addStretch();

    setLayout(mainLayout);

    // Fondo oscuro
    setStyleSheet("#riskFactorsCard { background-color: #111921; border-radius: 6px; }");
}

void RiskFactorsCard::addFactor(const QString &name, const QString &value, const QColor &valueColor, const QString &tooltip, bool addSeparator)
{
    auto *rowLayout = new QHBoxLayout();
    rowLayout->setSpacing(4);

    auto *nameLabel = new QLabel(name, this);
    nameLabel->setStyleSheet("font-size: 12px; color: #9BA5B1;");
    if (!tooltip.isEmpty()) {
        nameLabel->setToolTip(tooltip);
    }
    rowLayout->addWidget(nameLabel);

    rowLayout->addStretch();

    auto *valueLabel = new QLabel(value, this);
    const QString valueCss = QString("font-weight: 600; font-size: 12px; color: %1;").arg(valueColor.name());
    valueLabel->setStyleSheet(valueCss);
    rowLayout->addWidget(valueLabel);

    m_factorsLayout->addLayout(rowLayout);

    if (addSeparator) {
        auto *sep = new QFrame(this);
        sep->setFrameShape(QFrame::HLine);
        sep->setFrameShadow(QFrame::Plain);
        sep->setStyleSheet("color: #2E3740;");
        m_factorsLayout->addWidget(sep);
    }
} 