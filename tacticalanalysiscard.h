#ifndef TACTICALANALYSISCARD_H
#define TACTICALANALYSISCARD_H

#include "cardwidget.h"

class QVBoxLayout;
class QLabel;
class QProgressBar;

class TacticalAnalysisCard : public CardWidget
{
    Q_OBJECT

public:
    explicit TacticalAnalysisCard(QWidget *parent = nullptr);
    
    void setRachasPrecision(const QString &value);
    void setTasaOpcionTactica(const QString &value);
    void setPuntuacionSelectividad(double percentage);
    void setRachaMasLarga(const QString &value);

private:
    void setupUI();
    
    QLabel *m_rachasPrecisionLabel;
    QLabel *m_tasaOpcionTacticaLabel;
    QLabel *m_puntuacionSelectividadLabel;
    QProgressBar *m_selectividadBar;
    QLabel *m_rachaMasLargaLabel;
};

#endif // TACTICALANALYSISCARD_H 