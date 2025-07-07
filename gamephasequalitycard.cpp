#include "gamephasequalitycard.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>

// Widget personalizado para el gráfico de barras
class SimpleBarChart : public QWidget
{
public:
    SimpleBarChart(QWidget *parent = nullptr) : QWidget(parent) {
        setMinimumHeight(200);
    }
    
    void setValues(double apertura, double medioJuego, double final) {
        m_apertura = apertura;
        m_medioJuego = medioJuego;
        m_final = final;
        update();
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        
        // Fondo
        painter.fillRect(rect(), QColor("#0D1117"));
        
        // Calcular dimensiones
        int margin = 20;
        int barWidth = (width() - 4 * margin) / 3;
        int maxHeight = height() - 2 * margin - 30;
        double maxValue = qMax(qMax(m_apertura, m_medioJuego), m_final);
        if (maxValue == 0) maxValue = 10000;
        
        // Dibujar líneas de cuadrícula
        painter.setPen(QPen(QColor("#2E3740"), 1, Qt::DotLine));
        for (int i = 0; i <= 4; i++) {
            int y = margin + (maxHeight * i / 4);
            painter.drawLine(margin, y, width() - margin, y);
            
            // Etiquetas del eje Y
            painter.setPen(QColor("#9BA5B1"));
            painter.drawText(0, y - 5, margin - 5, 20, Qt::AlignRight | Qt::AlignVCenter, 
                           QString::number(int(maxValue * (4 - i) / 4)));
            painter.setPen(QPen(QColor("#2E3740"), 1, Qt::DotLine));
        }
        
        // Dibujar barras
        int x = margin;
        
        // Apertura
        int h1 = int(maxHeight * m_apertura / maxValue);
        painter.fillRect(x, margin + maxHeight - h1, barWidth, h1, QColor("#9B59B6"));
        painter.setPen(QColor("#9BA5B1"));
        painter.drawText(x, height() - 25, barWidth, 20, Qt::AlignCenter, "Apertura");
        
        // Medio Juego
        x += barWidth + margin;
        int h2 = int(maxHeight * m_medioJuego / maxValue);
        painter.fillRect(x, margin + maxHeight - h2, barWidth, h2, QColor("#3498DB"));
        painter.drawText(x, height() - 25, barWidth, 20, Qt::AlignCenter, "Medio Juego");
        
        // Final
        x += barWidth + margin;
        int h3 = int(maxHeight * m_final / maxValue);
        painter.fillRect(x, margin + maxHeight - h3, barWidth, h3, QColor("#2ECC71"));
        painter.drawText(x, height() - 25, barWidth, 20, Qt::AlignCenter, "Final");
    }

private:
    double m_apertura = 1257.27;
    double m_medioJuego = 7287.25;
    double m_final = 9258.26;
};

// Widget personalizado para gráfico circular
class SimplePieChart : public QWidget
{
public:
    SimplePieChart(QWidget *parent = nullptr) : QWidget(parent) {
        setMinimumSize(120, 120);
        setMaximumSize(150, 150);
    }
    
    void setValues(const QVector<double> &values, const QVector<QColor> &colors) {
        m_values = values;
        m_colors = colors;
        update();
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        
        int size = qMin(width(), height()) - 20;
        QRect pieRect((width() - size) / 2, (height() - size) / 2, size, size);
        
        // Calcular total
        double total = 0;
        for (double v : m_values) total += v;
        if (total == 0) return;
        
        // Dibujar sectores
        int startAngle = 90 * 16; // Empezar desde arriba
        for (int i = 0; i < m_values.size() && i < m_colors.size(); i++) {
            int spanAngle = int(m_values[i] / total * 360 * 16);
            painter.setBrush(m_colors[i]);
            painter.setPen(Qt::NoPen);
            painter.drawPie(pieRect, startAngle, -spanAngle);
            startAngle -= spanAngle;
        }
        
        // Círculo central (donut)
        int innerSize = size * 0.6;
        QRect innerRect((width() - innerSize) / 2, (height() - innerSize) / 2, innerSize, innerSize);
        painter.setBrush(QColor("#0D1117"));
        painter.drawEllipse(innerRect);
    }

private:
    QVector<double> m_values;
    QVector<QColor> m_colors;
};

GamePhaseQualityCard::GamePhaseQualityCard(QWidget *parent)
    : QFrame(parent),
      m_iconLabel(new QLabel("♔", this)),
      m_titleLabel(new QLabel("Calidad por Fase de Juego", this)),
      m_subtitleLabel(new QLabel("Análisis del rendimiento (ACPL) en cada fase de la partida.", this))
{
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Plain);
    setObjectName("gamePhaseQualityCard");

    // Layout principal
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(12);

    // Encabezado
    auto *headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(6);

    m_iconLabel->setFixedSize(18, 18);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setStyleSheet("font-size: 16px; color: #3498DB;");
    headerLayout->addWidget(m_iconLabel);

    m_titleLabel->setStyleSheet("font-weight: 700; font-size: 16px; color: #FFFFFF;");
    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch();

    mainLayout->addLayout(headerLayout);

    // Subtítulo
    m_subtitleLabel->setStyleSheet("font-size: 12px; color: #9BA5B1;");
    mainLayout->addWidget(m_subtitleLabel);

    // Título del gráfico
    auto *chartTitle = new QLabel("ACPL por Fase de Juego", this);
    chartTitle->setStyleSheet("font-size: 13px; color: #FFFFFF; margin-top: 10px;");
    mainLayout->addWidget(chartTitle);

    // Gráfico de barras
    m_barChartView = new SimpleBarChart(this);
    mainLayout->addWidget(m_barChartView);

    // Layout horizontal para los gráficos circulares
    auto *bottomLayout = new QHBoxLayout();
    bottomLayout->setSpacing(20);

    // Sección de distribución
    auto *distWidget = new QWidget(this);
    auto *distLayout = new QVBoxLayout(distWidget);
    distLayout->setSpacing(8);
    
    auto *distTitle = new QLabel("Distribución de Pérdidas por Fase", this);
    distTitle->setStyleSheet("font-size: 12px; color: #FFFFFF;");
    distLayout->addWidget(distTitle);
    
    m_pieChartView = new SimplePieChart(this);
    m_pieChartView->setValues({1257.27, 7287.25, 9258.26}, 
                             {QColor("#9B59B6"), QColor("#3498DB"), QColor("#2ECC71")});
    distLayout->addWidget(m_pieChartView, 0, Qt::AlignCenter);
    
    // Leyenda
    auto *legendLayout = new QHBoxLayout();
    legendLayout->setSpacing(15);
    
    auto addLegendItem = [&](const QColor &color, const QString &text, const QString &value) {
        auto *item = new QWidget(this);
        auto *itemLayout = new QHBoxLayout(item);
        itemLayout->setContentsMargins(0, 0, 0, 0);
        itemLayout->setSpacing(4);
        
        auto *colorBox = new QLabel(this);
        colorBox->setFixedSize(12, 12);
        colorBox->setStyleSheet(QString("background-color: %1; border-radius: 2px;").arg(color.name()));
        itemLayout->addWidget(colorBox);
        
        auto *label = new QLabel(text + " " + value, this);
        label->setStyleSheet("font-size: 11px; color: #9BA5B1;");
        itemLayout->addWidget(label);
        
        legendLayout->addWidget(item);
    };
    
    addLegendItem(QColor("#9B59B6"), "ACPL en Apertura", "1257.27");
    legendLayout->addStretch();
    distLayout->addLayout(legendLayout);
    
    auto *legendLayout2 = new QHBoxLayout();
    legendLayout2->setSpacing(15);
    addLegendItem(QColor("#3498DB"), "ACPL en Medio Juego", "7287.25");
    legendLayout2->addStretch();
    distLayout->addLayout(legendLayout2);
    
    auto *legendLayout3 = new QHBoxLayout();
    legendLayout3->setSpacing(15);
    addLegendItem(QColor("#2ECC71"), "ACPL en Final", "9258.26");
    legendLayout3->addStretch();
    distLayout->addLayout(legendLayout3);
    
    bottomLayout->addWidget(distWidget);

    // Sección de errores
    auto *errorWidget = new QWidget(this);
    auto *errorLayout = new QVBoxLayout(errorWidget);
    errorLayout->setSpacing(8);
    
    auto *errorTitle = new QLabel("Tasa de Errores Graves", this);
    errorTitle->setStyleSheet("font-size: 12px; color: #FFFFFF;");
    errorLayout->addWidget(errorTitle);
    
    m_errorChartView = new SimplePieChart(this);
    m_errorChartView->setValues({19.04, 80.96}, 
                               {QColor("#E74C3C"), QColor("#7F8C8D")});
    errorLayout->addWidget(m_errorChartView, 0, Qt::AlignCenter);
    
    // Leyenda de errores
    auto *errorLegendLayout = new QHBoxLayout();
    errorLegendLayout->setSpacing(15);
    addLegendItem(QColor("#E74C3C"), "Tasa de Errores Graves", "19.04%");
    errorLegendLayout->addStretch();
    errorLayout->addLayout(errorLegendLayout);
    
    bottomLayout->addWidget(errorWidget);

    mainLayout->addLayout(bottomLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);

    // Fondo oscuro
    setStyleSheet("#gamePhaseQualityCard { background-color: #111921; border-radius: 8px; }");
}

void GamePhaseQualityCard::setACPLApertura(double value)
{
    // Actualizar valor en el gráfico
    if (m_barChartView) {
        // Por simplicidad, mantenemos los valores actuales
    }
}

void GamePhaseQualityCard::setACPLMedioJuego(double value)
{
    // Actualizar valor en el gráfico
}

void GamePhaseQualityCard::setACPLFinal(double value)
{
    // Actualizar valor en el gráfico
}

void GamePhaseQualityCard::setDistribucionPerdidas(double apertura, double medioJuego, double final)
{
    if (m_pieChartView) {
        m_pieChartView->setValues({apertura, medioJuego, final}, 
                        {QColor("#9B59B6"), QColor("#3498DB"), QColor("#2ECC71")});
    }
}

void GamePhaseQualityCard::setTasaErroresGraves(double percentage)
{
    if (m_errorChartView) {
        m_errorChartView->setValues({percentage, 100 - percentage}, 
                        {QColor("#E74C3C"), QColor("#7F8C8D")});
    }
} 