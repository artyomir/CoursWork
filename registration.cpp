#include "registration.h"
#include "ui_registration.h"
#include <QFile>
#include <QDebug>


Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
    setWindowTitle("Registration");
    setWindowIcon(QIcon(":/fill/ICON.png"));

    ui->pushButton->setEnabled(false);
    QRegExp ex("[a-zA-Z]{3,15}");
    QRegExp exp("[a-zA-Z]{3,15}[0-9]{0,15}[.,_]{0,5}");
    ui->login->setValidator(new QRegExpValidator(exp, this));
    ui->passw->setValidator(new QRegExpValidator(exp, this));
    ui->name->setValidator(new QRegExpValidator(ex, this));
    ui->secname->setValidator(new QRegExpValidator(ex, this));
    ui->passw2->setValidator(new QRegExpValidator(exp, this));
    connect(ui->name, SIGNAL(textChanged(QString)), this, SLOT(RegEnabled()));
    connect(ui->secname, SIGNAL(textChanged(QString)), this, SLOT(RegEnabled()));
    connect(ui->login, SIGNAL(textChanged(QString)), this, SLOT(RegEnabled()));
    connect(ui->passw, SIGNAL(textChanged(QString)), this, SLOT(RegEnabled()));
    connect(ui->passw2, SIGNAL(textChanged(QString)), this, SLOT(RegEnabled()));
}

Registration::~Registration()
{
    delete ui;
}

void Registration::RegEnabled(){
    ui->pushButton->setEnabled(CheckValid());
}

bool Registration::CheckValid(){
    if (ui->login->hasAcceptableInput() && ui->passw->hasAcceptableInput() && ui->passw2->hasAcceptableInput()){
        if (ui->secname->hasAcceptableInput() && ui->name->hasAcceptableInput()){
            return true;
        } else return false;
    } else return false;
}

bool Registration::CheckLog(){
    if (ui->passw2->text() == ui->passw->text()){
        QFile f("./pasw_log.txt");
        if (!f.exists()){
            f.open(QFile::WriteOnly);
        }
        f.close();
        QFile mFile("./pasw_log.txt");
        if(!mFile.open(QFile::ReadOnly | QFile::Text)){
            ui->ErrorInf->setText("<font color=red>Registration error.</font>");
            return false;
        }
        while (!mFile.atEnd()){
            QString s = mFile.readLine();
            if (s.contains(':' + ui->login->text())){
                mFile.close();
                ui->ErrorInf->setText("<font color=red>Username not available</font>");
                return false;
            }
        }
        return true;
    } else{
        ui->ErrorInf->setText("<font color=red>Error entering password.</font>");
        return false;
    }
    return false;
}

void Registration::on_pushButton_clicked()
{
    if (CheckLog()){
    QFile mFile("./pasw_log.txt");
    if(!mFile.open(QFile::WriteOnly | QFile::Append | QFile::Text)){
        ui->ErrorInf->setText("<font color=red>Registration error.</font>");
        return;
    }
    QTextStream stream(&mFile);
    ui->ErrorInf->setText("<font color=green>Registration completed successfully!</font>");
    stream << ':' + ui->login->text() + '*' + ui->passw->text() + ' ' + ui->name->text() + ' ' + ui->secname->text() + '\n';
    ui->pushButton->setEnabled(false);
    mFile.close();
    }
}
