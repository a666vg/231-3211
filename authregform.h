#ifndef AUTHREGFORM_H
#define AUTHREGFORM_H

#include <QWidget>

namespace Ui
{
class AuthRegForm;
}

class AuthRegForm : public QWidget
{
    Q_OBJECT

public:
    explicit AuthRegForm(QWidget *parent = nullptr);
    ~AuthRegForm();

private:
    Ui::AuthRegForm *ui;

private slots:
    void on_authButton_clicked();
    void on_regButton_clicked();
    void on_authChange_clicked();
    void on_regChange_clicked();

signals:
    void auth(QString log, QString pass);
    void reg(QString log, QString pass, QString email);
};

#endif // AUTHREGFORM_H
