#include "Chercheur.h"
//#include"ui_mainwindow.h"
#include<QtDebug>
#include <QObject>
#include <QSqlQuery>
//#include <QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include "connection.h"
#include <QMessageBox>


#include <iostream>
#include <vector>
#include<vector>

#include <algorithm>
#include <cmath>


#include <QVariant>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

#include"SmtpMime"
#include"arduino.h"
#include "notif.h"
#include <QMessageBox>

QT_CHARTS_USE_NAMESPACE

Chercheurs::Chercheurs()
{
    id_chercheur=0;
    cin_chercheur=0;
    telephone_chercheur=0;
    age_chercheur=0;
    nom_chercheur="";
    prenom_chercheur="";
    email_chercheur="";
}
Chercheurs::Chercheurs(int cin , QString nom , QString prenom, QString email, int tel ,int age )
{
    //this->id_chercheur=id;
    this->cin_chercheur=cin;
    this-> telephone_chercheur= tel;
    this->age_chercheur=age;
    this->nom_chercheur=nom;
    this->prenom_chercheur=prenom;
    this->email_chercheur=email;


}
bool Chercheurs:: ajouter()
{

    QSqlQuery query;

    //QString idc= QString ::number(id_chercheur);
    QString res= QString::number(cin_chercheur);
    QString res2= QString::number(age_chercheur);
    QString res3= QString::number(telephone_chercheur);


         query.prepare("INSERT INTO CHERCHEURS(CIN_CHERCHEUR,NOM_CHERCHEUR,PRENOM_CHERCHEUR,AGE_CHERCHEUR,TELEPHONE_CHERCHEUR,EMAIL_CHERCHEUR) "
                       "VALUES (:cin,:nom,:prenom,:age,:telephone,:email)");
       //  query.bindValue(":id",idc);
         query.bindValue(":cin",res);
         query.bindValue(":nom",nom_chercheur);
         query.bindValue(":prenom",prenom_chercheur);
         query.bindValue(":age",res2);
         query.bindValue(":telephone", res3);
         query.bindValue(":email",email_chercheur);

         return  query.exec();

}


bool Chercheurs::trouverChercheurById(int id_chercheur)
{
    QSqlQuery query;
    QString res= QString::number(id_chercheur);
    query.prepare("SELECT * FROM chercheurs WHERE id_chercheur LIKE :cin");
    query.bindValue(":cin", res);

    if (query.exec()) {
            if (query.next()) {
                int count = query.value(0).toInt();
                return (count > 0);
            }
        }

        return false;

}
bool Chercheurs::trouverChercheurByCin(int cin_chercheur)
{
    QSqlQuery query;
    QString res= QString::number(cin_chercheur);
    query.prepare("SELECT * FROM chercheurs WHERE cin_chercheur LIKE :cin");
    query.bindValue(":cin", res);

    if (query.exec()) {
            if (query.next()) {
                int count = query.value(0).toInt();
                return (count > 0);
            }
        }

        return false;

}

QSqlQueryModel *Chercheurs::afficher()
{
  QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("SELECT * FROM CHERCHEURS ");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id chercheur"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("cin chercheur"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom chercheur"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("prénom chercheur"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("age chercheur"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("télèphone chercheur"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr(" email chercheur"));
        return model;
}


bool Chercheurs::supprimer(int id_chercheur)
{
QSqlQuery query;
QString res= QString::number(id_chercheur);
query.prepare("Delete from chercheurs where id_chercheur = :id_chercheur ");
query.bindValue(":id_chercheur", res);
return query.exec();

}


bool Chercheurs::modifier(int id_chercheur)
{

QSqlQuery query;
QString res=QString::number(id_chercheur);
QString res1=QString::number(cin_chercheur);
QString res3=QString::number(age_chercheur);
QString res4=QString::number(telephone_chercheur);

query.prepare("UPDATE chercheurs SET cin_chercheur=:cin_chercheur , nom_chercheur=:nom_chercheur , prenom_chercheur=:prenom_chercheur , age_chercheur=:age_chercheur , telephone_chercheur=:telephone_chercheur , email_chercheur=:email_chercheur where id_chercheur=:id_chercheur");

   query.bindValue(":id_chercheur",res);
    query.bindValue(":cin_chercheur", res1);
    query.bindValue(":nom_chercheur",nom_chercheur);
    query.bindValue(":prenom_chercheur",prenom_chercheur);
    query.bindValue(":age_chercheur",res3);
    query.bindValue(":telephone_chercheur",res4);
    query.bindValue(":email_chercheur",email_chercheur);

return    query.exec();
}

//

QSqlQueryModel* Chercheurs::rechercher(QString nom_chercheur)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Utilisez le paramètre nom_chercheur dans la requête préparée pour rechercher en fonction du nom
    query.prepare("SELECT * FROM chercheurs WHERE nom_chercheur = :nom");
    query.bindValue(":nom", nom_chercheur);

    if (query.exec()) {
        model->setQuery(query);

        // Définir les en-têtes de colonne pour le modèle
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id chercheur"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("cin chercheur"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom chercheur"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("prénom chercheur"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("age chercheur"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("télèphone chercheur"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("email chercheur"));

        return model;
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        return nullptr;
    }
}

 void Chercheurs::cleartable(QTableView * table)
 {
     QSqlQueryModel *model= new QSqlQueryModel();
     model->clear();
     table->setModel(model);
 }




 QSqlQueryModel * Chercheurs::trier()
 {
     QSqlQueryModel * model= new QSqlQueryModel();

     model->setQuery("select * from Chercheurs ORDER BY id_chercheur ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("id chercheur"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("cin chercheur"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom chercheur"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("prénom chercheur"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("age chercheur"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("télèphone chercheur"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr(" email chercheur"));
         return model;
 }



 QSqlQueryModel * Chercheurs::trierDec()
 {
     QSqlQueryModel * model= new QSqlQueryModel();

     model->setQuery("select * from Chercheurs ORDER BY id_chercheur desc");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("id chercheur"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("cin chercheur"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom chercheur"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("prénom chercheur"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("age chercheur"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("télèphone chercheur"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr(" email chercheur"));
         return model;
 }

 void Chercheurs::genererStatistique(){

     using namespace std;
     double s1,s2,s3;
     QSqlQuery query , q1,q2,q3;
        query.exec("SELECT age_chercheur FROM Chercheurs");

        vector<int> ages;
        int total = 0;
        while (query.next()) {
            int age = query.value(0).toInt();
            ages.push_back(age);
            total += age;
        }

        //ta3tik el nb totale des chercheurs eli 3marhom mabin 0 w 18
        q1.prepare("SELECT count (*)  from chercheurs where age_chercheur  between 0 and 18 " );

                                           q1.exec();
                                            if (q1.next()) {
                                           s1= q1.value(0).toInt();}


       q2.prepare("SELECT count (*)  from chercheurs where age_chercheur  between 19 and 60 " );

             q2.exec();
             if (q2.next()) {
                s2= q2.value(0).toInt();}


         q3.prepare("SELECT count (*)  from chercheurs where age_chercheur >60 " );

                   q3.exec();
                   if (q3.next()) {
                      s3= q3.value(0).toInt();}

        //Les pourcentages::

                   float a1 = (s1/total)*100;
                   float a2 = (s2/total)*100;
                   float a3 = (s3/total)*100;



        // Calcul des statistiques
        int n = ages.size();
        double mean = static_cast<double>(total) / n;

        double sum_of_squared_diff = 0;
        for (int i = 0; i < n; i++) {
            sum_of_squared_diff += pow(ages[i] - mean, 2);
        }
        double stddev = sqrt(sum_of_squared_diff / n);

        int min_age = *min_element(ages.begin(), ages.end());
        int max_age = *max_element(ages.begin(), ages.end());


        //**********

        QPieSeries *series = new QPieSeries();
            //series->append("nombre totale des chercheurs ", total);
            series->append("le % de chercheurs entre 0 t 18 ",  a1);
            series->append("le % de chercheurs entre 19 t 60 ",  a2);
            series->append("le % de chercheurs est sup de 60 ",  a3);
            //series->append("L'age d'Écart type  ",  stddev);

            QPieSlice *slice = series->slices().at(1);
            slice->setExploded();
            slice->setLabelVisible();
            slice->setPen(QPen(Qt::darkBlue, 2));
            slice->setBrush(Qt::darkBlue);




            QChart *chart = new QChart(); //création du cercle
            chart->addSeries(series);
            chart->setTitle("statistique sur l'age des chercheurs");
            // chart->legend()->hide();

            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);


            //setLayout(chartView);
           // setCentralWidget(chartView);
            chartView->resize(1268,748);

            chartView->show();

            //this->lower();
            //chartView->raise();
            //chartView->setFocus();
           // chartView->setVisible(true);
            // chartView->raise();
             // this->show();




 }


 //*********historique********


 bool Chercheurs::ajouter_historique(QString n)
 {
     QSqlQuery query;
     //QString res= QString::number(id);
     query.prepare("INSERT INTO HISTORIQUE_CHERCHEUR (NOM_HISTORIQUE, DATE_HISTORIQUE) "
                   "VALUES (:NOM,:DATE)");
     query.bindValue(":NOM", n);
     query.bindValue(":DATE", QDateTime::currentDateTime());

     return    query.exec();
 }




 QSqlQueryModel * Chercheurs ::afficher_historique()
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from HISTORIQUE_CHERCHEUR");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("date"));


     return model;
 }

 bool Chercheurs::supprimer_historique()
 {
     QSqlQuery query;
     //QString res= QString::number(idd);
     query.prepare("Delete from HISTORIQUE_CHERCHEUR ");
     //query.bindValue(":id", res);
     return    query.exec();
 }


 // Arduino **

 void Chercheurs:: flemme(){


     Chercheurs C;




    // QObject::connect (A. getserial() , SIGNAL (readyRead()) ,this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite & la reception du signal readyRead (reception des données) .




         // This is a first demo application of the SmtpClient for Qt project

         // First we need to create an SmtpClient object
         // We will use the Gmail's smtp server (smtp.gmail.com, port 465, ssl)


 }
