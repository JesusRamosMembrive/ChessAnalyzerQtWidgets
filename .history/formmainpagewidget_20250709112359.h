#ifndef FORMMAINPAGEWIDGET_H
#define FORMMAINPAGEWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include "serverstatusmanager.h"
#include <QList>

class QFrame;
class QHBoxLayout;
class QVBoxLayout;
class PlayerCardWidget;

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

    // Muestra placeholder "No players analyzed" cuando la lista esté vacía.
    void showNoPlayersPlaceholder();

private slots:
    void onRetryConnection();

    // Recibe lista de jugadores desde el ServerStatusManager
    void onPlayersUpdated(const QList<PlayerInfo> &players);

    void onPlayerClicked(const QString &username);

private:
    QLineEdit *usernameInput;

    void clearFrame(QFrame *frame);
};

#endif // FORMMAINPAGEWIDGET_H
