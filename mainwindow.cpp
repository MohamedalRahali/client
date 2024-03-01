#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include<QString>
#include<QIntValidator>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>










MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

    {

      ui->setupUi(this);
      ui->CIN_CLIENT->setFocus();
      setTabOrder(ui->CIN_CLIENT, ui->NOM_CLIENT);
      ui->CIN_CLIENT->setValidator( new QIntValidator(100, 99999999, this));
       ui->POSTALE_CLIENT->setValidator( new QIntValidator(100, 9999, this));

       ui->NUMERO_CLIENT->setValidator( new QIntValidator(0, 99999999, this));

       ui->tab_client->setModel(E.afficher());
 }
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_PB_AJOUTER_clicked()
{
    int CIN_CLIENT=ui->CIN_CLIENT->text().toInt();
    QString NOM_CLIENT=ui->NOM_CLIENT->text();
    QString PRENOM_CLIENT=ui->PRENOM_CLIENT->text();
    int  NUMERO_CLIENT=ui->NUMERO_CLIENT->text().toInt();
    QString ADRESSE_CLIENT=ui->ADRESSE_CLIENT->text();
    QString MAIL_CLIENT=ui->MAIL_CLIENT->text();
    QString VILLE=ui->VILLE_CLIENT->text();
    int CODE_POSTALE_CLIENT=ui->POSTALE_CLIENT->text().toInt();
    QDate DATE_NAISSANCE = ui->DATE_CLIENT->date();


    Client E(CIN_CLIENT,NOM_CLIENT,PRENOM_CLIENT ,NUMERO_CLIENT,ADRESSE_CLIENT,MAIL_CLIENT,VILLE,CODE_POSTALE_CLIENT,DATE_NAISSANCE);


    bool test =E.ajouter();

    if(test)
    {   QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("ajout effectué\n "
                                             "Click cancel to exit."), QMessageBox::Cancel);
        ui->tab_client->setModel(E.afficher());
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("not OK"),
                              QObject::tr("ajout non affecté.\n"
                                          "Click Cancel to exit."),QMessageBox::Cancel);
    }
}




void MainWindow::on_BP_SPPRIMER_clicked()
{
   Client E1;
   E1.setCIN_CLIENT(ui->CIN_SUPP->text().toInt());
   bool test=E1.supprimer(E1.getCIN_CLIENT());
   if(test)

              {

           QMessageBox::information(nullptr, QObject::tr("done"),

                           QObject::tr("suppression avec succés.\n"

                                          "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_client->setModel(E.afficher());

              }

              else
                  QMessageBox::critical(nullptr, QObject::tr("failed"),

                              QObject::tr("suppression failed.\n"

                                          "Click Cancel to exit."), QMessageBox::Cancel);

   }














