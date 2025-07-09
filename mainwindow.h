#pragma once

#include "formmainpagewidget.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <formmainpagewidget.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void goToResultsPage();
    void goToMainPage();
    void onStartAnalysis();

private:
    QStackedWidget *stackedWidget;
    QWidget *mainPage;
    QWidget *resultsPage;
    QLineEdit *usernameInput;
    FormMainPageWidget *mainPageWidget;
    
    void setupMainPage();
    void setupResultsPage();
    QWidget* createAnalysisCard(const QString &title, const QString &description, const QString &iconText, const QString &iconColor);
    QWidget* createPlayerCard(const QString &username, const QString &status, const QString &games, const QString &date);
};
