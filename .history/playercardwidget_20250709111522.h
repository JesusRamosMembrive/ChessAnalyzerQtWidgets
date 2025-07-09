#pragma once

#include <QFrame>
#include "serverstatusmanager.h"  // Para PlayerInfo

class QLabel;
class QPushButton;

//!  \brief Tarjeta visual para un jugador analizado.
//!
//!  Muestra avatar, username, status, juegos totales, juegos procesados y la fecha
//!  de finalización.  Emite clicked(username) al hacer clic en cualquier parte
//!  de la tarjeta.
class PlayerCardWidget : public QFrame
{
    Q_OBJECT
public:
    explicit PlayerCardWidget(const PlayerInfo &info, QWidget *parent = nullptr);

signals:
    void clicked(const QString &username);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    void buildUi(const PlayerInfo &info);

    QLabel *m_avatarLabel {nullptr};
    QLabel *m_nameLabel {nullptr};
    QLabel *m_gamesLabel {nullptr};
    QLabel *m_statusLabel {nullptr};
    QLabel *m_dateLabel {nullptr};
    QPushButton *m_deleteButton {nullptr};
    QString m_username;
}; 