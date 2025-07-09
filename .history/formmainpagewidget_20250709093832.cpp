#include "formmainpagewidget.h"
#include "ui_formmainpagewidget.h"
#include "connectionerrorwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPalette>
#include <QColor>
#include <QString>
#include <QLineEdit>
#include <QFrame>
#include <qimage.h>
#include <QPixmap>

#include <QDebug>



FormMainPageWidget::FormMainPageWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormMainPageWidget)
{
    ui->setupUi(this);

    // Por ahora, asumimos que no hay conexión al backend y mostramos el placeholder
    showConnectionErrorPlaceholder();
}

FormMainPageWidget::~FormMainPageWidget()
{
    delete ui;
}

// Implementación de createAnalysisCard adaptada de MainWindow
QWidget* FormMainPageWidget::createAnalysisCard(const QString &title, const QString &description, const QString &iconText, const QString &iconColor)
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
    auto *iconLabel = new QLabel(iconText);
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setStyleSheet(
        QString("color: %1; font-size: 24px; background-color: %1; color: white; "
                "border-radius: 8px; padding: 8px; max-width: 40px; max-height: 40px;").arg(iconColor)
    );
    iconLabel->setFixedSize(40, 40);
    auto *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setWordWrap(true);
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

void FormMainPageWidget::showConnectionErrorPlaceholder()
{
    if (!ui || !ui->frameAnalyzedPlayer)
        return;

    // Si el frame ya tiene un layout, lo limpiamos
    QLayout *oldLayout = ui->frameAnalyzedPlayer->layout();
    
    if (oldLayout) {
        QLayoutItem *child;
        while ((child = oldLayout->takeAt(0)) != nullptr) {
            if (child->widget()) {
                child->widget()->deleteLater();
            }
            delete child;
        }
        delete oldLayout;
    }

    // Nuevo layout centrado
    auto *layout = new QVBoxLayout(ui->frameAnalyzedPlayer);
    layout->setContentsMargins(32, 32, 32, 32);
    layout->setAlignment(Qt::AlignCenter);

    // Crear el widget de error
    auto *errorWidget = new ConnectionErrorWidget(ui->frameAnalyzedPlayer);
    connect(errorWidget, &ConnectionErrorWidget::retryClicked, this, &FormMainPageWidget::onRetryConnection);

    layout->addWidget(errorWidget);
}

void FormMainPageWidget::onRetryConnection()
{
    // Aquí se podría volver a intentar la conexión. Por ahora, simplemente volvemos a mostrar el placeholder
    showConnectionErrorPlaceholder();
}
