#include "logindialog.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QHBoxLayout>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Inicio de sesión"));
    setModal(true);

    // Crear widgets
    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);

    // Layouts
    auto *formLayout = new QFormLayout;
    formLayout->addRow(tr("Usuario:"), usernameEdit);
    formLayout->addRow(tr("Contraseña:"), passwordEdit);

    auto *loginBtn = new QPushButton(tr("Iniciar"), this);
    auto *cancelBtn = new QPushButton(tr("Cancelar"), this);

    // Conexiones
    connect(loginBtn, &QPushButton::clicked, this, &LoginDialog::handleLogin);
    connect(cancelBtn, &QPushButton::clicked, this, &LoginDialog::reject);

    auto *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(loginBtn);
    buttonLayout->addWidget(cancelBtn);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

void LoginDialog::handleLogin()
{
    const QString username = usernameEdit->text();
    const QString password = passwordEdit->text();

    if (username == "user" && password == "password") {
        accept();
    } else {
        QMessageBox::warning(this, tr("Login fallido"), tr("Credenciales incorrectas."));
    }
} 