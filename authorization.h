#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QMainWindow>
#include "registration.h"
#include "mainwindow.h"
namespace Ui {
class Authorization;
}

class Authorization : public QMainWindow
{
    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = 0);
    ~Authorization();
    bool CheckValid();

private slots:
    void on_buttonEnt_clicked();

    void on_buttonReg_clicked();

    void VhodEnabled();

private:
    Ui::Authorization *ui;
    MainWindow * window;

};

#endif // AUTHORIZATION_H
