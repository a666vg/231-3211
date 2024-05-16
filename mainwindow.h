#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui
{
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void solution(QString text);

private slots:
    void on_changeButton_clicked();
    void on_solutionButton_clicked();

private:
    Ui::MainWindow *ui;

    enum Task {vigenereEncrypt, sha256, splineMethod, gradientDescent};
    Task currentTask;

signals:
    void encrypt(QString text, QString key);
    void hash(QString text);
    void spline(QString pointA, QString pointB, QString pointC);
    void gradient(QString learningRate, QString maxIterations, QString precision);
};

#endif // MAINWINDOW_H
