#ifndef FORMMAINPAGEWIDGET_H
#define FORMMAINPAGEWIDGET_H

#include <QWidget>
#include <QLineEdit>
class QFrame;
class QHBoxLayout;
class QVBoxLayout;

namespace Ui {
class FormMainPageWidget;
}

class FormMainPageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FormMainPageWidget(QWidget *parent = nullptr);
    ~FormMainPageWidget();

private:
    Ui::FormMainPageWidget *ui;
    // Punteros a widgets generados en UI

    void setupMainPage();
    QWidget* createAnalysisCard(const QString &title, const QString &description, const QString &iconText, const QString &iconColor);

    // Muestra un placeholder con error de conexión dentro del frame de jugadores analizados
    void showConnectionErrorPlaceholder();

private slots:
    void onRetryConnection();

private:
    QLineEdit *usernameInput;
};

#endif // FORMMAINPAGEWIDGET_H
