#ifndef CLIENT_H
#define CLIENT_H
#include <QString>

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>



class Client
{ int CIN_CLIENT;
   QString NOM_CLIENT;
   QString PRENOM_CLIENT;
   int NUMERO_CLIENT;
   QString ADRESSE_CLIENT;
   QString MAIL_CLIENT;
   QString VILLE;
   int CODE_POSTALE_CLIENT;
   QDate DATE_NAISSANCE;



public:
    Client(){}
    Client(int,QString,QString,int,QString,QString,QString,int,QDate);
    int getCIN_CLIENT(){return CIN_CLIENT;}
    QString getNOM_CLIENT(){return NOM_CLIENT;}
    QString getPRENOM_CLIENT(){return PRENOM_CLIENT;}
    int getNUMERO(){return  NUMERO_CLIENT;}
    QString getADRESSE(){return ADRESSE_CLIENT;}
    QString getMAIL(){return MAIL_CLIENT;}
    QString getVILLE(){return VILLE;}
    int getCODE_POSTALE(){return CODE_POSTALE_CLIENT;}
    QDate getDATE_NAISSANCE() { return DATE_NAISSANCE; }


     void setCIN_CLIENT(int n){CIN_CLIENT=n;};
     void setNOM_CLIENT(QString n){NOM_CLIENT=n;};
     void setPRENOM_CLIENT(QString n){PRENOM_CLIENT=n;};
     void setNUMERO(int n){ NUMERO_CLIENT=n;};
     void setADRESSE(QString n){ADRESSE_CLIENT=n;};
     void setMAIL(QString n){MAIL_CLIENT=n;};
     void setVILLE(QString n){VILLE=n;};
     void setCODE_POSTALE(int n){CODE_POSTALE_CLIENT=n;};
     void setDATE_NAISSANCE(QDate date) { DATE_NAISSANCE = date; };


     bool nomPrenomValides(const QString &text);
     bool ajouter();
     bool modifier();

      QSqlQueryModel *afficher_NOM(QString ch);
         QSqlQueryModel *afficher_PRENOM(QString ch);
         QSqlQueryModel *afficher_VILLE(QString ch);
         QSqlQueryModel *afficher_choix(QString choix);




     QSqlQueryModel* afficher();
     bool supprimer(int);



};

#endif // CLIENT_H
