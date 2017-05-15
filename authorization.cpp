#include "authorization.h"
#include "ui_authorization.h"
#include "mainwindow.h"
#include <QString>
#include <QFile>
#include <QDebug>

Authorization::Authorization(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Authorization)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/fill/ICON.png"));

    ui->buttonEnt->setEnabled(false);
    QRegExp exp("[a-zA-Z]{3,15}[0-9]{0,15}[.,_]{0,5}");
    ui->login->setValidator(new QRegExpValidator(exp, this));
    ui->password->setValidator(new QRegExpValidator(exp, this));
    connect(ui->login, SIGNAL(textChanged(QString)),this, SLOT(VhodEnabled()));
    connect(ui->password, SIGNAL(textChanged(QString)),this, SLOT(VhodEnabled()));
    setWindowTitle("DUBKI");
}

bool Authorization::CheckValid(){
    if (ui->login->hasAcceptableInput() && ui->password->hasAcceptableInput()){
        return true;
    } else return false;
}

Authorization::~Authorization()
{
    delete ui;
}

void Authorization::on_buttonEnt_clicked()
{
    QFile f("./pasw_log.txt");
    if (!f.exists()){
        f.open(QFile::WriteOnly);
    }
    f.close();
    QFile mFile("./pasw_log.txt");
    if(!mFile.open(QFile::ReadOnly | QFile::Text)){
        ui->info->setText("<font color=red>Error, try again later.</font>");
        return;
    }
    while (!mFile.atEnd()){
        QString s = mFile.readLine();
        if (s.contains(':' + ui->login->text()) && s.contains('*' + ui->password->text())){
            mFile.close();
            QString student = s.split(" ").at(1).trimmed() + " " + s.split(" ").at(2).trimmed();
            qDebug() << student;
            window = new MainWindow(student);
            window->show();
            this->close();
            return;
        }
    }
    ui->info->setText("<font color=red>Incorrect login or password.</font>");
    mFile.close();
    return;
}

void Authorization::VhodEnabled(){
    ui->buttonEnt->setEnabled(CheckValid());
}

void Authorization::on_buttonReg_clicked()
{
    Registration w;
    w.show();
    w.exec();
}
