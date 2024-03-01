#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QSqlQueryModel>

#include <QSqlError>

#include <QDate>

#include <QtSql>

Client::Client(int CIN_CLIENT,QString NOM_CLIENT,QString PRENOM_CLIENT,int  NUMERO_CLIENT,QString ADRESSE_CLIENT,QString MAIL_CLIENT,QString VILLE,int CODE_POSTALE_CLIENT,QDate DATE_NAISSANCE)
{
    this->CIN_CLIENT=CIN_CLIENT;
    this->NOM_CLIENT=NOM_CLIENT;
    this->PRENOM_CLIENT=PRENOM_CLIENT;
    this-> NUMERO_CLIENT= NUMERO_CLIENT;
    this->ADRESSE_CLIENT=ADRESSE_CLIENT;
    this->MAIL_CLIENT=MAIL_CLIENT;
    this->VILLE=VILLE;
    this->CODE_POSTALE_CLIENT=CODE_POSTALE_CLIENT;
    this->DATE_NAISSANCE = DATE_NAISSANCE;
}

bool Client::nomPrenomValides(const QString &text)
{

    QRegularExpression regex("^[A-Za-z\\s]+$");
    return regex.match(text).hasMatch();
}
bool Client::ajouter()
{
    QSqlQuery query;
    QString CIN_String = QString::number(CIN_CLIENT);
    QString NUMERO_String = QString::number(NUMERO_CLIENT);
    QString CODE_POSTALE_CLIENT_String = QString::number(CODE_POSTALE_CLIENT);
    QDate dateActuelle = QDate::currentDate();
    QDate dateMinimum = dateActuelle.addYears(-10); // Soustraire 10 ans à la date actuelle.

    if (DATE_NAISSANCE.isValid() && DATE_NAISSANCE >= QDate(1900, 1, 1) && DATE_NAISSANCE <= dateMinimum)
        {
       QString DATE_NAISSANCE_String = DATE_NAISSANCE.toString("yyyy-MM-dd");

    query.prepare("INSERT INTO CLIENT (CIN_CLIENT, NOM_CLIENT, PRENOM_CLIENT, NUMERO_CLIENT, ADRESSE_CLIENT, MAIL_CLIENT, VILLE, CODE_POSTAL_CLIENT, DATE_NAISSANCE) "
                  "VALUES (:CIN_CLIENT, :NOM_CLIENT, :PRENOM_CLIENT, :NUMERO_CLIENT, :ADRESSE_CLIENT, :MAIL_CLIENT, :VILLE, :CODE_POSTALE_CLIENT, :DATE_NAISSANCE)");
    query.bindValue(":CIN_CLIENT", CIN_String);
    query.bindValue(":NOM_CLIENT", NOM_CLIENT);
    query.bindValue(":PRENOM_CLIENT", PRENOM_CLIENT);
    if (!nomPrenomValides(NOM_CLIENT)) {
        qDebug() << "Nom invalide : " << NOM_CLIENT;
        return false;
    }

    query.bindValue(":NUMERO_CLIENT", NUMERO_String);
    query.bindValue(":ADRESSE_CLIENT", ADRESSE_CLIENT);
    query.bindValue(":MAIL_CLIENT", MAIL_CLIENT);
    if (!MAIL_CLIENT.contains('@') || !MAIL_CLIENT.contains('.')) {
        qDebug() << "Adresse email invalide : " << MAIL_CLIENT;
        return false;
    }
    query.bindValue(":VILLE", VILLE);
    query.bindValue(":CODE_POSTALE_CLIENT", CODE_POSTALE_CLIENT_String);
    query.bindValue(":DATE_NAISSANCE", DATE_NAISSANCE);



    qDebug() << "Requête SQL : " << query.lastQuery();

    if (query.exec())
    {
        qDebug() << "Ajout réussi.";
        return true;
    }
    else
    {
        qDebug() << "Échec de l'ajout du client : " << query.lastError().text();
        return false;
    }
    }
    else
    {// La date n'est pas valide
        qDebug() << "Date de naissance invalide.";
        return false;
    }

}




 QSqlQueryModel *Client::afficher()
 {   QSqlQueryModel* model=new QSqlQueryModel();
     model->setQuery("SELECT* FROM CLIENT");
     for (int row = 0; row < model->rowCount(); ++row)
     {
            QModelIndex index = model->index(row, 0);
            QVariant data = index.data();
            if (data.canConvert<double>()) {
                double numeroClient = data.toDouble();
                model->setData(index, QString::number(numeroClient, 'f', 0)); // 'f' pour format fixe, 0 pour aucune décimale
            }
     }
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN_CLIENT"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_CLIENT"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_CLIENT"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO_CLIENT"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE_CLIENT"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL_CLIENT"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("VILLE"));
     model->setHeaderData(7, Qt::Horizontal, QObject::tr("CODE_POSTAL_CLIENT"));
     model->setHeaderData(8, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
     return  model;
 }
 bool Client::supprimer(int)
 {
     QSqlQuery query;
     query.prepare("Delete from CLIENT where CIN_CLIENT=:CIN_CLIENT ");
          query.bindValue(":CIN_CLIENT",CIN_CLIENT);
     qDebug() << "Requête SQL : " << query.lastQuery();
     if (query.exec())
     {   qDebug() << "Ajout réussi.";
         return true;
     }
     else
     {
         qDebug() << "Échec de l'ajout : " << query.lastError().text();
         return false;
     }
 }

//******************************affichage *****************************************************
QSqlQueryModel * Client::afficher_NOM(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT where NOM_CLIENT= '"+ch+"' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN_CLIENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_CLIENT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_CLIENT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO_CLIENT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("MAIL_CLIENT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ADRESSE_CLIENT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("VILLE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("CODE_POSTAL_CLIENT"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));


    return model;
}
QSqlQueryModel *Client::afficher_PRENOM(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT where PRENOM_CLIENT= '"+ch+"' ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN_CLIENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_CLIENT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_CLIENT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO_CLIENT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("MAIL_CLIENT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ADRESSE_CLIENT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("VILLE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("CODE_POSTAL_CLIENT"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));


    return model;
}
QSqlQueryModel *Client::afficher_VILLE(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT where VILLE= '"+ch+"' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN_CLIENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_CLIENT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_CLIENT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO_CLIENT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("MAIL_CLIENT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ADRESSE_CLIENT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("VILLE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("CODE_POSTAL_CLIENT"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    return model;
}









