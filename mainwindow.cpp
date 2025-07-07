#include "mainwindow.h"
#include "cardwidget.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Widget central
    auto *central = new QWidget(this);
    auto *layout = new QHBoxLayout(central);
    layout->setSpacing(12);
    layout->setContentsMargins(12, 12, 12, 12);

    // Añadimos las distintas cajas/metricas
    auto *riskCard = new CardWidget("Puntuación de Riesgo");
    riskCard->setValue("20/100", QColor("#2ECC71"));
    riskCard->setSubtitle("Evaluación general de sospecha");
    layout->addWidget(riskCard);

    auto *gamesCard = new CardWidget("Partidas Analizadas");
    gamesCard->setValue("98", QColor("#2ECC71"));
    gamesCard->setSubtitle("Del 4/7/2025 al 4/7/2025");
    layout->addWidget(gamesCard);

    auto *eloCard = new CardWidget("Rendimiento Intrínseco");
    eloCard->setValue("-188", QColor("#2ECC71"));
    eloCard->setSubtitle("ELO estimado según sus jugadas");
    layout->addWidget(eloCard);

    auto *suddenCard = new CardWidget("Mejora Súbita");
    suddenCard->setValue("Detectada", QColor("#FF8C00"));
    suddenCard->setSubtitle("Magnitud: 2191");
    layout->addWidget(suddenCard);

    setCentralWidget(central);

    setWindowTitle("Panel de Métricas");
}
