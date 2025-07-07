#include "mainwindow.h"
#include "cardwidget.h"
#include "metricscard.h"
#include "riskfactorscard.h"
#include "trendscard.h"
#include "roianalysiscard.h"
#include "openingpatternscard.h"
#include "gamephasequalitycard.h"
#include "timemanagementcard.h"
#include "clutchperformancecard.h"
#include "benchmarkingcard.h"
#include "tacticalanalysiscard.h"
#include "endgameanalysiscard.h"
#include "resumenanalisiscard.h"
#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Crear scroll area
    auto *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    
    // Widget contenedor para el scroll
    auto *scrollWidget = new QWidget();
    auto *layout = new QGridLayout(scrollWidget);
    layout->setSpacing(12);
    layout->setContentsMargins(12, 12, 12, 12);

    // Tarjeta de Resumen del Análisis (colocada al inicio)
    auto *resumenCard = new ResumenAnalisisCard();
    resumenCard->setPuntuacionRiesgoFinal("20/100", QColor("#2ECC71"));
    resumenCard->setPartidasAnalizadas("98", QColor("#3498DB"));
    resumenCard->setPartidasSospechosas("0", QColor("#9B59B6"));
    resumenCard->setConclusion("El análisis indica un riesgo MUY BAJO. Los patrones de juego son consistentes con comportamiento humano natural.");
    layout->addWidget(resumenCard, 0, 0, 1, 4); // Fila 0, ocupa las 4 columnas

    // Añadimos las distintas cajas/metricas
    auto *riskCard = new CardWidget("Puntuación de Riesgo");
    riskCard->setValue("20/100", QColor("#2ECC71"));
    riskCard->setSubtitle("Evaluación general de sospecha");
    layout->addWidget(riskCard, 1, 0);

    auto *gamesCard = new CardWidget("Partidas Analizadas");
    gamesCard->setValue("98", QColor("#2ECC71"));
    gamesCard->setSubtitle("Del 4/7/2025 al 4/7/2025");
    layout->addWidget(gamesCard, 1, 1);

    auto *eloCard = new CardWidget("Rendimiento Intrínseco");
    eloCard->setValue("-188", QColor("#2ECC71"));
    eloCard->setSubtitle("ELO estimado según sus jugadas");
    layout->addWidget(eloCard, 1, 2);

    auto *suddenCard = new CardWidget("Mejora Súbita");
    suddenCard->setValue("Detectada", QColor("#FF8C00"));
    suddenCard->setSubtitle("Magnitud: 2191");
    layout->addWidget(suddenCard, 1, 3);

    // Tarjeta con varias métricas de calidad
    auto *qualityCard = new MetricsCard();
    qualityCard->addMetric("Pérdida Media de Centipeones (ACPL)", "4808.16");
    qualityCard->addMetric("Desviación Estándar de ACPL", "6685.29");
    qualityCard->addMetric("Coincidencia con el Módulo", "26.96%");
    qualityCard->addMetric("Desviación Estándar de Coincidencia", "13.26%");
    qualityCard->addMetric("Rating de Rendimiento Intrínseco (IPR)", "-188");
    layout->addWidget(qualityCard, 2, 0, 1, 2); // Ocupa 2 columnas

    // Tarjeta de Factores de Riesgo
    auto *riskFactorsCard = new RiskFactorsCard();
    riskFactorsCard->addFactor("Step Function", "100%", QColor("#FF3333"), QString(), true);
    riskFactorsCard->addFactor("Nivel de Confianza", "0%", QColor("#FFFFFF"), "", false);
    layout->addWidget(riskFactorsCard, 2, 2, 1, 2); // Ocupa 2 columnas

    // Tarjeta de Tendencias
    auto *trendsCard = new TrendsCard();
    trendsCard->addTrend("Tendencia ACPL", "-159.37 cp/100 partidas", 85);
    trendsCard->addTrend("Tendencia Match Rate", "-1.29%/100 partidas", 45);
    trendsCard->setEvaluationStatus("Mejorando", QColor("#FF8C00"));
    layout->addWidget(trendsCard, 3, 0, 1, 4); // Ahora ocupa las 4 columnas

    // Tarjeta de Análisis Longitudinal (ROI)
    auto *roiCard = new ROIAnalysisCard();
    roiCard->setROIMedio("-188", QColor("#2ECC71"));
    roiCard->setROIMaximo("2514", QColor("#3498DB"));
    roiCard->setDesviacionROI("3364", QColor("#9B59B6"));
    layout->addWidget(roiCard, 4, 0, 1, 2); // Movido a fila 4

    // Tarjeta de Patrones de Apertura
    auto *openingCard = new OpeningPatternsCard();
    openingCard->setDiversidad(0.00);
    openingCard->setProfundidad(4.71);
    openingCard->setAmplitud(1);
    openingCard->setTasa2f3(87.04);
    layout->addWidget(openingCard, 4, 2, 1, 2); // Fila 4, columnas 2-3

    // Tarjeta de Calidad por Fase de Juego
    auto *gamePhaseCard = new GamePhaseQualityCard();
    gamePhaseCard->setACPLApertura(1257.27);
    gamePhaseCard->setACPLMedioJuego(7287.25);
    gamePhaseCard->setACPLFinal(9258.26);
    gamePhaseCard->setDistribucionPerdidas(1257.27, 7287.25, 9258.26);
    gamePhaseCard->setTasaErroresGraves(19.04);
    layout->addWidget(gamePhaseCard, 5, 0, 1, 4); // Fila 5, ocupa las 4 columnas

    // Tarjeta de Gestión del Tiempo
    auto *timeCard = new TimeManagementCard();
    timeCard->setTiempoMedioPorJugada("46.09s");
    timeCard->setVarianzaTiempo("110641.59");
    timeCard->setPuntuacionUniformidad(-8.22);
    timeCard->setPicosLag(91);
    layout->addWidget(timeCard, 6, 0, 1, 2); // Fila 6, columnas 0-1

    // Tarjeta de Precisión Bajo Presión
    auto *clutchCard = new ClutchPerformanceCard();
    clutchCard->setDiferenciaMediaClutch("9361.70");
    clutchCard->setPorcentajePartidasClutch(10.20);
    layout->addWidget(clutchCard, 6, 2, 1, 2); // Fila 6, columnas 2-3

    // Tarjeta de Benchmarking vs Pares
    auto *benchmarkingCard = new BenchmarkingCard();
    // Los valores por defecto ya están configurados en el constructor
    // Pero se pueden actualizar con:
    // benchmarkingCard->setACPLComparison(90, "Muy Alto (Top 10%)");
    // benchmarkingCard->setOpeningDiversityComparison(5, "Bajo (Bottom 25%)");
    // benchmarkingCard->setDirectComparisonACPL(0.00);
    // benchmarkingCard->setDirectComparisonCoincidence(0.00);
    layout->addWidget(benchmarkingCard, 7, 0, 1, 4); // Fila 7, ocupa las 4 columnas

    // Tarjeta de Análisis Táctico
    auto *tacticalCard = new TacticalAnalysisCard();
    // Los valores por defecto ya están configurados en el constructor
    layout->addWidget(tacticalCard, 8, 0, 1, 2); // Fila 8, columnas 0-1

    // Tarjeta de Análisis de Finales
    auto *endgameCard = new EndgameAnalysisCard();
    // Los valores por defecto ya están configurado en el constructor
    layout->addWidget(endgameCard, 8, 2, 1, 2); // Fila 8, columnas 2-3

    // Configurar el scroll area
    scrollArea->setWidget(scrollWidget);
    setCentralWidget(scrollArea);

    setWindowTitle("Panel de Métricas");
}
