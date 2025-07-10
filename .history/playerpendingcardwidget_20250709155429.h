#pragma once

#include <QFrame>
#include "serverstatusmanager.h"

class QLabel;
class QPushButton;
class QProgressBar;

//!  \brief Tarjeta para mostrar progreso de análisis "Pending".
class PlayerPendingCardWidget : public QFrame
{
    Q_OBJECT
public:
    explicit PlayerPendingCardWidget(const PlayerInfo &info, QWidget *parent = nullptr);
    void updateInfo(const PlayerInfo &info);

signals:
    void clicked(const QString &username);
    void cancelRequested(const QString &username);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    void buildUi(const PlayerInfo &info);
    void applyProgress(int progress, int doneGames, int totalGames);

    QString m_username;
    QLabel *m_avatarLabel {nullptr};
    QLabel *m_nameLabel {nullptr};
    QLabel *m_statusLabel {nullptr};
    QProgressBar *m_progressBar {nullptr};
    QLabel *m_progressInfoLabel {nullptr};
    QLabel *m_gamesLabel {nullptr};
    QLabel *m_startDateLabel {nullptr};
    QPushButton *m_cancelButton {nullptr};
}; 