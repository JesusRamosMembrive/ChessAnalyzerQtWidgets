#include "tacticalanalysiscard.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QFrame>

TacticalAnalysisCard::TacticalAnalysisCard(QWidget *parent)
    : CardWidget("⚡ Análisis Táctico", parent)
{
    setSubtitle("Patrones de precisión táctica y rachas de jugadas perfectas.");
    setupUI();
}

void TacticalAnalysisCard::setupUI()
{
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(layout());
    
    // Rachas de Precisión
    QFrame *rachasFrame = new QFrame();
    rachasFrame->setFrameStyle(QFrame::NoFrame);
    QHBoxLayout *rachasLayout = new QHBoxLayout(rachasFrame);
    rachasLayout->setContentsMargins(0, 0, 0, 0);
    
    QLabel *rachasLabel = new QLabel("Rachas de Precisión");
    rachasLabel->setStyleSheet("color: #BDC3C7; font-size: 13px;");
    
    QLabel *infoIcon1 = new QLabel("ⓘ");
    infoIcon1->setStyleSheet("color: #7F8C8D; font-size: 11px;");
    
    m_rachasPrecisionLabel = new QLabel("N/A");
    m_rachasPrecisionLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
    
    rachasLayout->addWidget(rachasLabel);
    rachasLayout->addWidget(infoIcon1);
    rachasLayout->addStretch();
    rachasLayout->addWidget(m_rachasPrecisionLabel);
    
    // Tasa de 2ª/3ª Opción Táctica
    QFrame *tasaFrame = new QFrame();
    tasaFrame->setFrameStyle(QFrame::NoFrame);
    QHBoxLayout *tasaLayout = new QHBoxLayout(tasaFrame);
    tasaLayout->setContentsMargins(0, 0, 0, 0);
    
    QLabel *tasaLabel = new QLabel("Tasa de 2ª/3ª Opción Táctica");
    tasaLabel->setStyleSheet("color: #BDC3C7; font-size: 13px;");
    
    QLabel *infoIcon2 = new QLabel("ⓘ");
    infoIcon2->setStyleSheet("color: #7F8C8D; font-size: 11px;");
    
    m_tasaOpcionTacticaLabel = new QLabel("N/A");
    m_tasaOpcionTacticaLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
    
    tasaLayout->addWidget(tasaLabel);
    tasaLayout->addWidget(infoIcon2);
    tasaLayout->addStretch();
    tasaLayout->addWidget(m_tasaOpcionTacticaLabel);
    
    // Puntuación de Selectividad
    QFrame *selectividadFrame = new QFrame();
    selectividadFrame->setFrameStyle(QFrame::NoFrame);
    QHBoxLayout *selectividadLayout = new QHBoxLayout(selectividadFrame);
    selectividadLayout->setContentsMargins(0, 0, 0, 0);
    
    QLabel *selectividadLabel = new QLabel("Puntuación de Selectividad");
    selectividadLabel->setStyleSheet("color: #BDC3C7; font-size: 13px;");
    
    QLabel *infoIcon3 = new QLabel("ⓘ");
    infoIcon3->setStyleSheet("color: #7F8C8D; font-size: 11px;");
    
    m_puntuacionSelectividadLabel = new QLabel("48.98%");
    m_puntuacionSelectividadLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
    
    selectividadLayout->addWidget(selectividadLabel);
    selectividadLayout->addWidget(infoIcon3);
    selectividadLayout->addStretch();
    selectividadLayout->addWidget(m_puntuacionSelectividadLabel);
    
    // Barra de progreso para selectividad
    m_selectividadBar = new QProgressBar();
    m_selectividadBar->setRange(0, 100);
    m_selectividadBar->setValue(49);
    m_selectividadBar->setTextVisible(false);
    m_selectividadBar->setFixedHeight(8);
    m_selectividadBar->setStyleSheet(
        "QProgressBar {"
        "    background-color: #34495E;"
        "    border-radius: 4px;"
        "}"
        "QProgressBar::chunk {"
        "    background-color: #3498DB;"
        "    border-radius: 4px;"
        "}"
    );
    
    // Racha Más Larga (ROI > 2.75)
    QFrame *rachaFrame = new QFrame();
    rachaFrame->setFrameStyle(QFrame::NoFrame);
    QHBoxLayout *rachaLayout = new QHBoxLayout(rachaFrame);
    rachaLayout->setContentsMargins(0, 0, 0, 0);
    
    QLabel *rachaLabel = new QLabel("Racha Más Larga (ROI > 2.75)");
    rachaLabel->setStyleSheet("color: #BDC3C7; font-size: 13px;");
    
    QLabel *infoIcon4 = new QLabel("ⓘ");
    infoIcon4->setStyleSheet("color: #7F8C8D; font-size: 11px;");
    
    m_rachaMasLargaLabel = new QLabel("7 partidas");
    m_rachaMasLargaLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
    
    rachaLayout->addWidget(rachaLabel);
    rachaLayout->addWidget(infoIcon4);
    rachaLayout->addStretch();
    rachaLayout->addWidget(m_rachaMasLargaLabel);
    
    // Añadir todos los widgets al layout principal
    mainLayout->addWidget(rachasFrame);
    mainLayout->addSpacing(8);
    mainLayout->addWidget(tasaFrame);
    mainLayout->addSpacing(8);
    mainLayout->addWidget(selectividadFrame);
    mainLayout->addWidget(m_selectividadBar);
    mainLayout->addSpacing(8);
    mainLayout->addWidget(rachaFrame);
}

void TacticalAnalysisCard::setRachasPrecision(const QString &value)
{
    m_rachasPrecisionLabel->setText(value);
}

void TacticalAnalysisCard::setTasaOpcionTactica(const QString &value)
{
    m_tasaOpcionTacticaLabel->setText(value);
}

void TacticalAnalysisCard::setPuntuacionSelectividad(double percentage)
{
    m_puntuacionSelectividadLabel->setText(QString::number(percentage, 'f', 2) + "%");
    m_selectividadBar->setValue(static_cast<int>(percentage));
}

void TacticalAnalysisCard::setRachaMasLarga(const QString &value)
{
    m_rachaMasLargaLabel->setText(value);
} 