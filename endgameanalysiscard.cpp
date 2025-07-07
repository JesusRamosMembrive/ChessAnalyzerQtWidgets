#include "endgameanalysiscard.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QFrame>

EndgameAnalysisCard::EndgameAnalysisCard(QWidget *parent)
    : CardWidget("🏆 Análisis de Finales", parent)
{
    setSubtitle("Eficiencia y precisión en la fase final de la partida");
    setupUI();
}

void EndgameAnalysisCard::setupUI()
{
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(layout());
    
    // Eficiencia de Conversión
    QFrame *eficienciaFrame = new QFrame();
    eficienciaFrame->setFrameStyle(QFrame::NoFrame);
    QHBoxLayout *eficienciaLayout = new QHBoxLayout(eficienciaFrame);
    eficienciaLayout->setContentsMargins(0, 0, 0, 0);
    
    QLabel *eficienciaLabel = new QLabel("Eficiencia de Conversión");
    eficienciaLabel->setStyleSheet("color: #BDC3C7; font-size: 13px;");
    
    QLabel *infoIcon1 = new QLabel("ⓘ");
    infoIcon1->setStyleSheet("color: #7F8C8D; font-size: 11px;");
    
    m_eficienciaConversionLabel = new QLabel("20%");
    m_eficienciaConversionLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
    
    eficienciaLayout->addWidget(eficienciaLabel);
    eficienciaLayout->addWidget(infoIcon1);
    eficienciaLayout->addStretch();
    eficienciaLayout->addWidget(m_eficienciaConversionLabel);
    
    // Barra de progreso para eficiencia
    m_eficienciaBar = new QProgressBar();
    m_eficienciaBar->setRange(0, 100);
    m_eficienciaBar->setValue(20);
    m_eficienciaBar->setTextVisible(false);
    m_eficienciaBar->setFixedHeight(8);
    m_eficienciaBar->setStyleSheet(
        "QProgressBar {"
        "    background-color: #34495E;"
        "    border-radius: 4px;"
        "}"
        "QProgressBar::chunk {"
        "    background-color: #E74C3C;"
        "    border-radius: 4px;"
        "}"
    );
    
    // Coincidencia con Tablebases
    QFrame *coincidenciaFrame = new QFrame();
    coincidenciaFrame->setFrameStyle(QFrame::NoFrame);
    QHBoxLayout *coincidenciaLayout = new QHBoxLayout(coincidenciaFrame);
    coincidenciaLayout->setContentsMargins(0, 0, 0, 0);
    
    QLabel *coincidenciaLabel = new QLabel("Coincidencia con Tablebases");
    coincidenciaLabel->setStyleSheet("color: #BDC3C7; font-size: 13px;");
    
    QLabel *infoIcon2 = new QLabel("ⓘ");
    infoIcon2->setStyleSheet("color: #7F8C8D; font-size: 11px;");
    
    m_coincidenciaTablebasesLabel = new QLabel("N/A");
    m_coincidenciaTablebasesLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
    
    coincidenciaLayout->addWidget(coincidenciaLabel);
    coincidenciaLayout->addWidget(infoIcon2);
    coincidenciaLayout->addStretch();
    coincidenciaLayout->addWidget(m_coincidenciaTablebasesLabel);
    
    // Desviación DTZ
    QFrame *desviacionFrame = new QFrame();
    desviacionFrame->setFrameStyle(QFrame::NoFrame);
    QHBoxLayout *desviacionLayout = new QHBoxLayout(desviacionFrame);
    desviacionLayout->setContentsMargins(0, 0, 0, 0);
    
    QLabel *desviacionLabel = new QLabel("Desviación DTZ");
    desviacionLabel->setStyleSheet("color: #BDC3C7; font-size: 13px;");
    
    QLabel *infoIcon3 = new QLabel("ⓘ");
    infoIcon3->setStyleSheet("color: #7F8C8D; font-size: 11px;");
    
    m_desviacionDTZLabel = new QLabel("N/A");
    m_desviacionDTZLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
    
    desviacionLayout->addWidget(desviacionLabel);
    desviacionLayout->addWidget(infoIcon3);
    desviacionLayout->addStretch();
    desviacionLayout->addWidget(m_desviacionDTZLabel);
    
    // Añadir todos los widgets al layout principal
    mainLayout->addWidget(eficienciaFrame);
    mainLayout->addWidget(m_eficienciaBar);
    mainLayout->addSpacing(8);
    mainLayout->addWidget(coincidenciaFrame);
    mainLayout->addSpacing(8);
    mainLayout->addWidget(desviacionFrame);
    mainLayout->addStretch();
}

void EndgameAnalysisCard::setEficienciaConversion(double percentage)
{
    m_eficienciaConversionLabel->setText(QString::number(percentage, 'f', 0) + "%");
    m_eficienciaBar->setValue(static_cast<int>(percentage));
}

void EndgameAnalysisCard::setCoincidenciaTablebases(const QString &value)
{
    m_coincidenciaTablebasesLabel->setText(value);
}

void EndgameAnalysisCard::setDesviacionDTZ(const QString &value)
{
    m_desviacionDTZLabel->setText(value);
} 