#include "formmainpagewidget.h"
#include "ui_formmainpagewidget.h"
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
