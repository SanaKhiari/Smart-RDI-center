#ifndef CHERCHEUR_H
#define CHERCHEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QTableView>
#include <vector>
#include <algorithm>
#include <cmath>
#include <QDate>

class Chercheurs{
        private:
            QString nom_chercheur;
            QString prenom_chercheur;
            QString email_chercheur;
            int cin_chercheur;
            int id_chercheur;
            int telephone_chercheur;
            int age_chercheur;

        public:
            Chercheurs();
            Chercheurs(int,QString,QString,QString,int,int);
            QString get_nomChercheur()const{return nom_chercheur;}
            QString get_prenomChercheur()const{return prenom_chercheur;}
            QString get_emailChercheur()const{return email_chercheur;}
            int get_ageChercheur()const{return age_chercheur;}
            int get_cinChercheur()const{return cin_chercheur;}
            int get_telephoneChercheur()const{return telephone_chercheur;}
            bool ajouter();
            QSqlQueryModel * afficher();
            bool supprimer(int);
            bool modifier(int);
            bool trouverChercheurById(int);
            bool trouverChercheurByCin(int);
           // Chercheurs findCherch(int);
            Chercheurs Mcher(int);
            void cleartable(QTableView * table);
            QSqlQueryModel* rechercher(QString nom_chercheur);
            QSqlQueryModel * trier();
             QSqlQueryModel * trierDec();
             void genererStatistique();
              bool ajouter_historique(QString n);
              QSqlQueryModel * afficher_historique();
              bool supprimer_historique();
              void flemme();
};


#endif // CHERCHEUR_H
