#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentTask = vigenereEncrypt;
    ui->taskLabel->setText("Vigenere Encrypt");
    ui->param1Edit->setPlaceholderText("String");
    ui->param2Edit->setPlaceholderText("Key");
    ui->param3Edit->setVisible(false);
    ui->solutionLabel->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_solutionButton_clicked()
{
    if (currentTask == vigenereEncrypt)
    {
        emit encrypt(ui->param1Edit->text(), ui->param2Edit->text());
    }
    else if (currentTask == sha256)
    {
        emit hash(ui->param1Edit->text());
    }
    else if (currentTask == splineMethod)
    {
        emit spline(ui->param1Edit->text(), ui->param2Edit->text(), ui->param3Edit->text());
    }
    else if (currentTask == gradientDescent)
    {
        emit gradient(ui->param1Edit->text(), ui->param2Edit->text(), ui->param3Edit->text());
    }
}

void MainWindow::on_changeButton_clicked()
{
    if (currentTask == vigenereEncrypt)
    {
        currentTask = sha256;
        ui->taskLabel->setText("Sha-256");
        ui->param1Edit->setPlaceholderText("String");
        ui->param2Edit->setVisible(false);
        ui->solutionLabel->setText("");
    }
    else if (currentTask == sha256)
    {
        currentTask = splineMethod;
        ui->taskLabel->setText("Spline Method");
        ui->param1Edit->setPlaceholderText("Point A (Format: x,y)");
        ui->param2Edit->setPlaceholderText("Point B (Format: x,y)");
        ui->param3Edit->setPlaceholderText("Point C (Format: x,y)");
        ui->param2Edit->setVisible(true);
        ui->param3Edit->setVisible(true);
        ui->solutionLabel->setText("");
    }
    else if (currentTask == splineMethod)
    {
        currentTask = gradientDescent;
        ui->taskLabel->setText("Gradient Descent");
        ui->param1Edit->setPlaceholderText("Learning Rate");
        ui->param2Edit->setPlaceholderText("Max Iterations");
        ui->param3Edit->setPlaceholderText("Precision");
        ui->solutionLabel->setText("");
    }
    else if (currentTask == gradientDescent)
    {
        currentTask = vigenereEncrypt;
        ui->taskLabel->setText("Vigenere Encrypt");
        ui->param1Edit->setPlaceholderText("String");
        ui->param2Edit->setPlaceholderText("Key");
        ui->param3Edit->setVisible(false);
        ui->solutionLabel->setText("");
    }
}

void MainWindow::solution(QString text)
{
    ui->solutionLabel->setText(text);
}

