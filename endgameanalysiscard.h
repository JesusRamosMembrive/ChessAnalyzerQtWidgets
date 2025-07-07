#ifndef ENDGAMEANALYSISCARD_H
#define ENDGAMEANALYSISCARD_H

#include "cardwidget.h"

class QVBoxLayout;
class QLabel;
class QProgressBar;

class EndgameAnalysisCard : public CardWidget
{
    Q_OBJECT

public:
    explicit EndgameAnalysisCard(QWidget *parent = nullptr);
    
    void setEficienciaConversion(double percentage);
    void setCoincidenciaTablebases(const QString &value);
    void setDesviacionDTZ(const QString &value);

private:
    void setupUI();
    
    QLabel *m_eficienciaConversionLabel;
    QProgressBar *m_eficienciaBar;
    QLabel *m_coincidenciaTablebasesLabel;
    QLabel *m_desviacionDTZLabel;
};

#endif // ENDGAMEANALYSISCARD_H 