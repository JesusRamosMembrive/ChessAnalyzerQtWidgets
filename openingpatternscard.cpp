#include "openingpatternscard.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QProgressBar>

OpeningPatternsCard::OpeningPatternsCard(QWidget *parent)
    : QFrame(parent),
      m_iconLabel(new QLabel("♟", this)),
      m_titleLabel(new QLabel("Patrones de Apertura", this)),
      m_subtitleLabel(new QLabel("Análisis del repertorio de aperturas.", this)),
      m_metricsLayout(new QHBoxLayout()),
      m_diversidadBar(nullptr),
      m_profundidadBar(nullptr),
      m_amplitudBar(nullptr),
      m_tasaBar(nullptr),
      m_diversidadValue(nullptr),
      m_profundidadValue(nullptr),
      m_amplitudValue(nullptr),
      m_tasaValue(nullptr)
{
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Plain);
    setObjectName("openingPatternsCard");

    // Layout principal
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(12);

    // Encabezado con icono y título
    auto *headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(6);

    m_iconLabel->setFixedSize(18, 18);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setStyleSheet("font-size: 16px; color: #F1C40F;");
    headerLayout->addWidget(m_iconLabel);

    m_titleLabel->setStyleSheet("font-weight: 700; font-size: 16px; color: #FFFFFF;");
    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch();

    mainLayout->addLayout(headerLayout);

    // Subtítulo
    m_subtitleLabel->setStyleSheet("font-size: 12px; color: #9BA5B1;");
    mainLayout->addWidget(m_subtitleLabel);

    // Espacio adicional
    mainLayout->addSpacing(20);

    // Layout horizontal para las métricas
    m_metricsLayout->setSpacing(20);
    m_metricsLayout->setContentsMargins(0, 0, 0, 0);

    // Crear las cuatro métricas
    auto *diversidadWidget = createMetricWidget("Diversidad de Aperturas (Entropía)", "0.00", 0.0);
    m_diversidadBar = diversidadWidget->findChild<QProgressBar*>("progressBar");
    m_diversidadValue = diversidadWidget->findChild<QLabel*>("valueLabel");
    m_metricsLayout->addWidget(diversidadWidget);

    auto *profundidadWidget = createMetricWidget("Profundidad de Novedad", "4.71", 47.1);
    m_profundidadBar = profundidadWidget->findChild<QProgressBar*>("progressBar");
    m_profundidadValue = profundidadWidget->findChild<QLabel*>("valueLabel");
    m_metricsLayout->addWidget(profundidadWidget);

    auto *amplitudWidget = createMetricWidget("Amplitud de Aperturas", "1", 10.0);
    m_amplitudBar = amplitudWidget->findChild<QProgressBar*>("progressBar");
    m_amplitudValue = amplitudWidget->findChild<QLabel*>("valueLabel");
    m_metricsLayout->addWidget(amplitudWidget);

    auto *tasaWidget = createMetricWidget("Tasa de 2ª/3ª Opción", "87.04%", 87.04);
    m_tasaBar = tasaWidget->findChild<QProgressBar*>("progressBar");
    m_tasaValue = tasaWidget->findChild<QLabel*>("valueLabel");
    m_metricsLayout->addWidget(tasaWidget);

    mainLayout->addLayout(m_metricsLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);

    // Fondo oscuro
    setStyleSheet("#openingPatternsCard { background-color: #111921; border-radius: 8px; }");
}

QWidget* OpeningPatternsCard::createMetricWidget(const QString &label, const QString &value, 
                                                double progress, const QString &tooltip)
{
    auto *widget = new QWidget(this);
    auto *layout = new QVBoxLayout(widget);
    layout->setSpacing(8);

    // Label con tooltip
    auto *labelWidget = new QLabel(label, widget);
    labelWidget->setStyleSheet("font-size: 11px; color: #9BA5B1;");
    labelWidget->setWordWrap(true);
    if (!tooltip.isEmpty()) {
        labelWidget->setToolTip(tooltip);
    }
    layout->addWidget(labelWidget);

    // Valor
    auto *valueLabel = new QLabel(value, widget);
    valueLabel->setObjectName("valueLabel");
    valueLabel->setStyleSheet("font-weight: 600; font-size: 14px; color: #FFFFFF;");
    layout->addWidget(valueLabel);

    // Barra de progreso
    auto *progressBar = new QProgressBar(widget);
    progressBar->setObjectName("progressBar");
    progressBar->setRange(0, 100);
    progressBar->setValue(static_cast<int>(progress));
    progressBar->setTextVisible(false);
    progressBar->setFixedHeight(6);
    
    // Estilo de la barra
    QString progressStyle = R"(
        QProgressBar {
            background-color: #2E3740;
            border-radius: 3px;
        }
        QProgressBar::chunk {
            background-color: #3498DB;
            border-radius: 3px;
        }
    )";
    progressBar->setStyleSheet(progressStyle);
    
    layout->addWidget(progressBar);
    layout->addStretch();

    widget->setLayout(layout);
    return widget;
}

void OpeningPatternsCard::setDiversidad(double value)
{
    if (m_diversidadValue && m_diversidadBar) {
        m_diversidadValue->setText(QString::number(value, 'f', 2));
        m_diversidadBar->setValue(static_cast<int>(value * 100)); // Asumiendo escala 0-1
    }
}

void OpeningPatternsCard::setProfundidad(double value)
{
    if (m_profundidadValue && m_profundidadBar) {
        m_profundidadValue->setText(QString::number(value, 'f', 2));
        m_profundidadBar->setValue(static_cast<int>(value * 10)); // Asumiendo escala 0-10
    }
}

void OpeningPatternsCard::setAmplitud(int value)
{
    if (m_amplitudValue && m_amplitudBar) {
        m_amplitudValue->setText(QString::number(value));
        m_amplitudBar->setValue(value); // Asumiendo escala 0-100
    }
}

void OpeningPatternsCard::setTasa2f3(double percentage)
{
    if (m_tasaValue && m_tasaBar) {
        m_tasaValue->setText(QString::number(percentage, 'f', 2) + "%");
        m_tasaBar->setValue(static_cast<int>(percentage));
    }
} 