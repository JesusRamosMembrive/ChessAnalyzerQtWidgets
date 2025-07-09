#ifndef CONNECTIONERRORWIDGET_H
#define CONNECTIONERRORWIDGET_H

#include <QFrame>

class QLabel;
class QPushButton;

class ConnectionErrorWidget : public QFrame
{
    Q_OBJECT
public:
    explicit ConnectionErrorWidget(QWidget *parent = nullptr);

signals:
    void retryClicked();

private slots:
    void onRetry();

private:
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_descLabel;
    QLabel *m_detailsLabel;
    QPushButton *m_retryButton;
};

#endif // CONNECTIONERRORWIDGET_H 