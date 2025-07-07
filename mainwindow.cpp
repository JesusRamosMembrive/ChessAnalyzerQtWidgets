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
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QColor>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Crear el QStackedWidget como widget central
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
    
    // Crear las páginas
    mainPage = new QWidget();
    resultsPage = new QWidget();
    
    // Configurar cada página
    setupMainPage();
    setupResultsPage();
    
    // Añadir las páginas al stack
    stackedWidget->addWidget(mainPage);    // Índice 0
    stackedWidget->addWidget(resultsPage); // Índice 1
    
    // Mostrar la página principal al inicio
    stackedWidget->setCurrentIndex(0);
    
    setWindowTitle("Chess Analyzer");
}

void MainWindow::setupMainPage()
{
    auto *mainLayout = new QVBoxLayout(mainPage);
    mainLayout->setContentsMargins(40, 30, 40, 30);
    mainLayout->setSpacing(40);
    
    // Header con logo y título
    auto *headerLayout = new QHBoxLayout();
    
    // Logo (lado izquierdo)
    auto *logoLayout = new QHBoxLayout();
    auto *logoIcon = new QLabel("♛");
    logoIcon->setStyleSheet(
        "color: #2ECC71;"
        "font-size: 24px;"
        "font-weight: bold;"
        "background-color: #2ECC71;"
        "color: white;"
        "border-radius: 8px;"
        "padding: 8px;"
        "max-width: 40px;"
        "max-height: 40px;"
    );
    logoIcon->setAlignment(Qt::AlignCenter);
    
    auto *logoText = new QLabel("Chess Analyzer");
    logoText->setStyleSheet("color: white; font-size: 18px; font-weight: bold; margin-left: 10px;");
    
    logoLayout->addWidget(logoIcon);
    logoLayout->addWidget(logoText);
    logoLayout->addStretch();
    
    headerLayout->addLayout(logoLayout);
    headerLayout->addStretch();
    
    mainLayout->addLayout(headerLayout);
    
    // Título principal centrado
    auto *titleLabel = new QLabel("Analyze Chess Performance");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: white; font-size: 36px; font-weight: bold; margin: 20px 0;");
    mainLayout->addWidget(titleLabel);
    
    // Subtítulo
    auto *subtitleLabel = new QLabel("Discover patterns, detect anomalies, and gain insights from chess.com game data");
    subtitleLabel->setAlignment(Qt::AlignCenter);
    subtitleLabel->setStyleSheet("color: #BDC3C7; font-size: 16px; margin-bottom: 30px;");
    mainLayout->addWidget(subtitleLabel);
    
    // Sección New Analysis
    auto *analysisWidget = new QWidget();
    analysisWidget->setFixedSize(400, 180);
    analysisWidget->setStyleSheet(
        "QWidget {"
        "   background-color: #3A4B5C;"
        "   border-radius: 12px;"
        "   padding: 20px;"
        "}"
    );
    
    auto *analysisLayout = new QVBoxLayout(analysisWidget);
    analysisLayout->setSpacing(15);
    
    // Icono y título de New Analysis
    auto *analysisHeaderLayout = new QHBoxLayout();
    auto *searchIcon = new QLabel("🔍");
    searchIcon->setStyleSheet("font-size: 18px;");
    
    auto *analysisTitle = new QLabel("New Analysis");
    analysisTitle->setStyleSheet("color: white; font-size: 18px; font-weight: bold;");
    
    analysisHeaderLayout->addWidget(searchIcon);
    analysisHeaderLayout->addWidget(analysisTitle);
    analysisHeaderLayout->addStretch();
    analysisLayout->addLayout(analysisHeaderLayout);
    
    // Instrucción
    auto *instructionLabel = new QLabel("Enter a chess.com username to analyze");
    instructionLabel->setStyleSheet("color: #BDC3C7; font-size: 14px;");
    analysisLayout->addWidget(instructionLabel);
    
    // Campo de entrada
    usernameInput = new QLineEdit();
    usernameInput->setPlaceholderText("Enter chess.com username");
    usernameInput->setStyleSheet(
        "QLineEdit {"
        "   background-color: #485A6B;"
        "   border: 1px solid #5D6D7E;"
        "   border-radius: 6px;"
        "   padding: 12px;"
        "   color: #FFFFFF;"
        "   font-size: 14px;"
        "}"
        "QLineEdit::placeholder {"
        "   color: #BDC3C7;"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #3498DB;"
        "   background-color: #526A80;"
        "}"
    );
    analysisLayout->addWidget(usernameInput);
    
    // Botón Start Analysis
    auto *startBtn = new QPushButton("Start Analysis");
    startBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #27AE60;"
        "   color: #FFFFFF;"
        "   border: none;"
        "   border-radius: 6px;"
        "   padding: 12px;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "   min-height: 20px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2ECC71;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #229954;"
        "}"
    );
    connect(startBtn, &QPushButton::clicked, this, &MainWindow::onStartAnalysis);
    analysisLayout->addWidget(startBtn);
    
    // Centrar el widget de análisis
    auto *centerLayout = new QHBoxLayout();
    centerLayout->addStretch();
    centerLayout->addWidget(analysisWidget);
    centerLayout->addStretch();
    mainLayout->addLayout(centerLayout);
    
    // Grid de tarjetas de análisis
    auto *cardsLayout = new QHBoxLayout();
    cardsLayout->setSpacing(20);
    
    auto *openingCard = createAnalysisCard("Opening Entropy", "Analyze opening diversity vs ELO consistency", "📊", "#3498DB");
    auto *timingCard = createAnalysisCard("Move Timing", "Detect suspicious timing patterns", "⏱️", "#9B59B6");
    auto *statsCard = createAnalysisCard("Win/Loss Stats", "Comprehensive game outcome analysis", "📈", "#2ECC71");
    auto *comebackCard = createAnalysisCard("Comeback Analysis", "Identify dramatic game turnarounds", "⚡", "#E67E22");
    
    cardsLayout->addWidget(openingCard);
    cardsLayout->addWidget(timingCard);
    cardsLayout->addWidget(statsCard);
    cardsLayout->addWidget(comebackCard);
    
    mainLayout->addLayout(cardsLayout);
    
    // Sección Analyzed Players
    auto *playersWidget = new QWidget();
    playersWidget->setStyleSheet(
        "QWidget {"
        "   background-color: #3A4B5C;"
        "   border-radius: 12px;"
        "   padding: 20px;"
        "}"
    );
    
    auto *playersLayout = new QVBoxLayout(playersWidget);
    
    // Header de Analyzed Players
    auto *playersHeaderLayout = new QHBoxLayout();
    auto *playersIcon = new QLabel("👥");
    playersIcon->setStyleSheet("font-size: 18px;");
    
    auto *playersTitle = new QLabel("Analyzed Players");
    playersTitle->setStyleSheet("color: white; font-size: 18px; font-weight: bold;");
    
    playersHeaderLayout->addWidget(playersIcon);
    playersHeaderLayout->addWidget(playersTitle);
    playersHeaderLayout->addStretch();
    playersLayout->addLayout(playersHeaderLayout);
    
    // Estado vacío - No players analyzed
    auto *emptyStateLayout = new QVBoxLayout();
    emptyStateLayout->setAlignment(Qt::AlignCenter);
    emptyStateLayout->setSpacing(10);
    
    // Icono de usuario
    auto *userIcon = new QLabel("👤");
    userIcon->setAlignment(Qt::AlignCenter);
    userIcon->setStyleSheet("font-size: 48px; color: #7F8C8D; margin: 20px 0 10px 0;");
    
    // Texto "No players analyzed"
    auto *noPlayersLabel = new QLabel("No players analyzed");
    noPlayersLabel->setAlignment(Qt::AlignCenter);
    noPlayersLabel->setStyleSheet("color: #BDC3C7; font-size: 16px; font-weight: bold;");
    
    // Texto de instrucción
    auto *instructionText = new QLabel("Start analyzing a player to see results here");
    instructionText->setAlignment(Qt::AlignCenter);
    instructionText->setStyleSheet("color: #7F8C8D; font-size: 12px; margin-bottom: 20px;");
    
    emptyStateLayout->addWidget(userIcon);
    emptyStateLayout->addWidget(noPlayersLabel);
    emptyStateLayout->addWidget(instructionText);
    
    playersLayout->addLayout(emptyStateLayout);
    
    mainLayout->addWidget(playersWidget);
    mainLayout->addStretch();
    
    // Establecer el fondo
    mainPage->setStyleSheet("background-color: #1A1A1A;");
}

void MainWindow::setupResultsPage()
{
    // Crear scroll area
    auto *scrollArea = new QScrollArea(resultsPage);
    scrollArea->setWidgetResizable(true);
    
    // Widget contenedor para el scroll
    auto *scrollWidget = new QWidget();
    auto *layout = new QGridLayout(scrollWidget);
    layout->setSpacing(12);
    layout->setContentsMargins(12, 12, 12, 12);

    // Botón para volver a la página principal
    auto *backBtn = new QPushButton("← Volver al Inicio");
    backBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: #3498DB;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 6px;"
        "   padding: 8px 16px;"
        "   font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2980B9;"
        "}"
    );
    connect(backBtn, &QPushButton::clicked, this, &MainWindow::goToMainPage);
    layout->addWidget(backBtn, 0, 0, 1, 1, Qt::AlignLeft);

    // Tarjeta de Resumen del Análisis (colocada al inicio)
    auto *resumenCard = new ResumenAnalisisCard();
    resumenCard->setPuntuacionRiesgoFinal("20/100", QColor("#2ECC71"));
    resumenCard->setPartidasAnalizadas("98", QColor("#3498DB"));
    resumenCard->setPartidasSospechosas("0", QColor("#9B59B6"));
    resumenCard->setConclusion("El análisis indica un riesgo MUY BAJO. Los patrones de juego son consistentes con comportamiento humano natural.");
    layout->addWidget(resumenCard, 1, 0, 1, 4); // Fila 1, ocupa las 4 columnas

    // Añadimos las distintas cajas/metricas
    auto *riskCard = new CardWidget("Puntuación de Riesgo");
    riskCard->setValue("20/100", QColor("#2ECC71"));
    riskCard->setSubtitle("Evaluación general de sospecha");
    layout->addWidget(riskCard, 2, 0);

    auto *gamesCard = new CardWidget("Partidas Analizadas");
    gamesCard->setValue("98", QColor("#2ECC71"));
    gamesCard->setSubtitle("Del 4/7/2025 al 4/7/2025");
    layout->addWidget(gamesCard, 2, 1);

    auto *eloCard = new CardWidget("Rendimiento Intrínseco");
    eloCard->setValue("-188", QColor("#2ECC71"));
    eloCard->setSubtitle("ELO estimado según sus jugadas");
    layout->addWidget(eloCard, 2, 2);

    auto *suddenCard = new CardWidget("Mejora Súbita");
    suddenCard->setValue("Detectada", QColor("#FF8C00"));
    suddenCard->setSubtitle("Magnitud: 2191");
    layout->addWidget(suddenCard, 2, 3);

    // Tarjeta con varias métricas de calidad
    auto *qualityCard = new MetricsCard();
    qualityCard->addMetric("Pérdida Media de Centipeones (ACPL)", "4808.16");
    qualityCard->addMetric("Desviación Estándar de ACPL", "6685.29");
    qualityCard->addMetric("Coincidencia con el Módulo", "26.96%");
    qualityCard->addMetric("Desviación Estándar de Coincidencia", "13.26%");
    qualityCard->addMetric("Rating de Rendimiento Intrínseco (IPR)", "-188");
    layout->addWidget(qualityCard, 3, 0, 1, 2); // Ocupa 2 columnas

    // Tarjeta de Factores de Riesgo
    auto *riskFactorsCard = new RiskFactorsCard();
    riskFactorsCard->addFactor("Step Function", "100%", QColor("#FF3333"), QString(), true);
    riskFactorsCard->addFactor("Nivel de Confianza", "0%", QColor("#FFFFFF"), "", false);
    layout->addWidget(riskFactorsCard, 3, 2, 1, 2); // Ocupa 2 columnas

    // Tarjeta de Tendencias
    auto *trendsCard = new TrendsCard();
    trendsCard->addTrend("Tendencia ACPL", "-159.37 cp/100 partidas", 85);
    trendsCard->addTrend("Tendencia Match Rate", "-1.29%/100 partidas", 45);
    trendsCard->setEvaluationStatus("Mejorando", QColor("#FF8C00"));
    layout->addWidget(trendsCard, 4, 0, 1, 4); // Ahora ocupa las 4 columnas

    // Tarjeta de Análisis Longitudinal (ROI)
    auto *roiCard = new ROIAnalysisCard();
    roiCard->setROIMedio("-188", QColor("#2ECC71"));
    roiCard->setROIMaximo("2514", QColor("#3498DB"));
    roiCard->setDesviacionROI("3364", QColor("#9B59B6"));
    layout->addWidget(roiCard, 5, 0, 1, 2); // Movido a fila 5

    // Tarjeta de Patrones de Apertura
    auto *openingCard = new OpeningPatternsCard();
    openingCard->setDiversidad(0.00);
    openingCard->setProfundidad(4.71);
    openingCard->setAmplitud(1);
    openingCard->setTasa2f3(87.04);
    layout->addWidget(openingCard, 5, 2, 1, 2); // Fila 5, columnas 2-3

    // Tarjeta de Calidad por Fase de Juego
    auto *gamePhaseCard = new GamePhaseQualityCard();
    gamePhaseCard->setACPLApertura(1257.27);
    gamePhaseCard->setACPLMedioJuego(7287.25);
    gamePhaseCard->setACPLFinal(9258.26);
    gamePhaseCard->setDistribucionPerdidas(1257.27, 7287.25, 9258.26);
    gamePhaseCard->setTasaErroresGraves(19.04);
    layout->addWidget(gamePhaseCard, 6, 0, 1, 4); // Fila 6, ocupa las 4 columnas

    // Tarjeta de Gestión del Tiempo
    auto *timeCard = new TimeManagementCard();
    timeCard->setTiempoMedioPorJugada("46.09s");
    timeCard->setVarianzaTiempo("110641.59");
    timeCard->setPuntuacionUniformidad(-8.22);
    timeCard->setPicosLag(91);
    layout->addWidget(timeCard, 7, 0, 1, 2); // Fila 7, columnas 0-1

    // Tarjeta de Precisión Bajo Presión
    auto *clutchCard = new ClutchPerformanceCard();
    clutchCard->setDiferenciaMediaClutch("9361.70");
    clutchCard->setPorcentajePartidasClutch(10.20);
    layout->addWidget(clutchCard, 7, 2, 1, 2); // Fila 7, columnas 2-3

    // Tarjeta de Benchmarking vs Pares
    auto *benchmarkingCard = new BenchmarkingCard();
    layout->addWidget(benchmarkingCard, 8, 0, 1, 4); // Fila 8, ocupa las 4 columnas

    // Tarjeta de Análisis Táctico
    auto *tacticalCard = new TacticalAnalysisCard();
    layout->addWidget(tacticalCard, 9, 0, 1, 2); // Fila 9, columnas 0-1

    // Tarjeta de Análisis de Finales
    auto *endgameCard = new EndgameAnalysisCard();
    layout->addWidget(endgameCard, 9, 2, 1, 2); // Fila 9, columnas 2-3

    // Configurar el scroll area
    scrollArea->setWidget(scrollWidget);
    
    // Layout principal para la página de resultados
    auto *mainLayout = new QVBoxLayout(resultsPage);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(scrollArea);
}

void MainWindow::goToResultsPage()
{
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::goToMainPage()
{
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::onStartAnalysis()
{
    QString username = usernameInput->text().trimmed();
    if (!username.isEmpty()) {
        // Por ahora, simplemente navegar a la página de resultados
        // Aquí es donde se ejecutaría el análisis real
        goToResultsPage();
    }
}

QWidget* MainWindow::createAnalysisCard(const QString &title, const QString &description, const QString &iconText, const QString &iconColor)
{
    auto *card = new QWidget();
    card->setFixedSize(180, 120);
    card->setStyleSheet(
        "QWidget {"
        "   background-color: #3A4B5C;"
        "   border-radius: 12px;"
        "   padding: 15px;"
        "}"
        "QWidget:hover {"
        "   background-color: #455A6B;"
        "}"
    );
    
    auto *layout = new QVBoxLayout(card);
    layout->setSpacing(8);
    
    // Icono
    auto *iconLabel = new QLabel(iconText);
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setStyleSheet(
        QString("color: %1; font-size: 24px; background-color: %1; color: white; "
                "border-radius: 8px; padding: 8px; max-width: 40px; max-height: 40px;").arg(iconColor)
    );
    iconLabel->setFixedSize(40, 40);
    
    // Título
    auto *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setWordWrap(true);
    
    // Descripción
    auto *descLabel = new QLabel(description);
    descLabel->setStyleSheet("color: #BDC3C7; font-size: 11px;");
    descLabel->setAlignment(Qt::AlignCenter);
    descLabel->setWordWrap(true);
    
    layout->addWidget(iconLabel, 0, Qt::AlignCenter);
    layout->addWidget(titleLabel);
    layout->addWidget(descLabel);
    layout->addStretch();
    
    return card;
}

QWidget* MainWindow::createPlayerCard(const QString &username, const QString &status, const QString &games, const QString &date)
{
    auto *card = new QWidget();
    card->setStyleSheet(
        "QWidget {"
        "   background-color: #2C3E50;"
        "   border-radius: 8px;"
        "   padding: 12px;"
        "   margin: 5px 0;"
        "}"
    );
    
    auto *layout = new QHBoxLayout(card);
    
    // Avatar (inicial del nombre)
    auto *avatar = new QLabel("A");
    avatar->setStyleSheet(
        "background-color: #3498DB;"
        "color: white;"
        "border-radius: 16px;"
        "font-size: 14px;"
        "font-weight: bold;"
        "padding: 8px;"
    );
    avatar->setFixedSize(32, 32);
    avatar->setAlignment(Qt::AlignCenter);
    
    // Información del usuario
    auto *userInfo = new QVBoxLayout();
    auto *nameLabel = new QLabel(username);
    nameLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
    
    auto *infoLabel = new QLabel(QString("Games: %1    Done: %2").arg(games, date));
    infoLabel->setStyleSheet("color: #BDC3C7; font-size: 11px;");
    
    userInfo->addWidget(nameLabel);
    userInfo->addWidget(infoLabel);
    userInfo->setSpacing(2);
    
    // Status
    auto *statusLabel = new QLabel(status);
    statusLabel->setStyleSheet(
        "background-color: #2ECC71;"
        "color: white;"
        "border-radius: 10px;"
        "padding: 4px 8px;"
        "font-size: 11px;"
        "font-weight: bold;"
    );
    
    // Fecha
    auto *dateLabel = new QLabel("📅 Finished: " + date);
    dateLabel->setStyleSheet("color: #BDC3C7; font-size: 11px;");
    
    // Botón eliminar
    auto *deleteBtn = new QPushButton("🗑️");
    deleteBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"
        "   border: none;"
        "   color: #E74C3C;"
        "   font-size: 14px;"
        "   padding: 4px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #E74C3C;"
        "   color: white;"
        "   border-radius: 4px;"
        "}"
    );
    deleteBtn->setFixedSize(30, 30);
    
    layout->addWidget(avatar);
    layout->addLayout(userInfo);
    layout->addStretch();
    layout->addWidget(statusLabel);
    layout->addWidget(dateLabel);
    layout->addWidget(deleteBtn);
    
    return card;
}
