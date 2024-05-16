#include "authregform.h"
#include "ui_authregform.h"

AuthRegForm::AuthRegForm(QWidget *parent) : QWidget(parent), ui(new Ui::AuthRegForm)
{
    ui->setupUi(this);
    ui->emailEdit->setVisible(false);
    ui->regLabel->setVisible(false);
    ui->regButton->setVisible(false);
    ui->regChange->setVisible(false);
}

AuthRegForm::~AuthRegForm()
{
    delete ui;
}


void AuthRegForm::on_authButton_clicked()
{
    emit auth(ui->loginEdit->text(), ui->passEdit->text());
}


void AuthRegForm::on_regButton_clicked()
{
    emit reg(ui->loginEdit->text(), ui->passEdit->text(), ui->emailEdit->text());
}


void AuthRegForm::on_authChange_clicked()
{
    ui->emailEdit->setVisible(true);
    ui->regLabel->setVisible(true);
    ui->regButton->setVisible(true);
    ui->regChange->setVisible(true);

    ui->authLabel->setVisible(false);
    ui->authButton->setVisible(false);
    ui->authChange->setVisible(false);
}


void AuthRegForm::on_regChange_clicked()
{
    ui->authLabel->setVisible(true);
    ui->authButton->setVisible(true);
    ui->authChange->setVisible(true);

    ui->emailEdit->setVisible(false);
    ui->regLabel->setVisible(false);
    ui->regButton->setVisible(false);
    ui->regChange->setVisible(false);
}

