#include "dialog.h"
#include "ui_dialog.h"

#include "Chercheur.h"
#include"connection.h"
#include <QMessageBox>
#include <QSqlQuery>

#include <QString>
#include <QSqlQueryModel>

#include<QtDebug>
#include <QObject>
//#include <QPrintDialog>
#include <QtPrintSupport/QPrinter>

#include "mainwindow.h"
#include "ui_mainwindow.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QPixmap bkgnd("C:/Users/21624/Documents/C++/backgroundDesktop.png");
            bkgnd=bkgnd.scaled(this->size(),Qt::IgnoreAspectRatio);
            QPalette p;
            p.setBrush(QPalette::Background, bkgnd);
            this->setPalette(p);
}

Dialog::~Dialog()
{
    delete ui;
}



/*
void Dialog::afficherD(int id_chercheur){

    Chercheurs c;
    c.Mcher(id_chercheur);
    ui->lineEdit_cin_chercheur_modif->setText(QString::number(c.get_cinChercheur()));
    ui->nom_cherchreur_lineEdit_modif->setText(c.get_nomChercheur());
    ui->lineEdit_prenom_chercheur_Modif->setText(c.get_prenomChercheur());
    ui->lineEdit_email_chercheur_modif->setText(c.get_emailChercheur());
    ui->spinBox_age_chercheur_modif->setValue(c.get_ageChercheur());
    ui->lineEdit_telephone_chercheur_modif->setText(QString::number(c.get_telephoneChercheur()));

}
*/
/*void Dialog:: Mcher(int id_chercheur){
    QSqlQuery query;
    QString res= QString::number(id_chercheur);
    query.prepare("SELECT * FROM chercheurs WHERE id = :id");
    query.bindValue(":id", res);
    if (!query.exec()) {
          QMessageBox::critical(this, tr("Erreur de requête"),
              tr("La requête de sélection a échoué : %1").arg(query.lastError().text()));
          return;
      }

      if (query.next()) {
          int cin = query.value("cin_chercheur").toInt();
          QString nom = query.value("nom_chercheur").toString();
          QString prenom = query.value("prenom_chercheur").toString();
          QString email = query.value("email_chercheur").toString();
          int age = query.value("age_chercheur").toInt();
          int telephone = query.value("telephone_chercheur").toInt();
           Chercheurs c(cin,nom,prenom,email,age,telephone);
          ui->lineEdit_cin_chercheur_modif->setText(QString::number(c.get_cinChercheur()));
          ui->nom_cherchreur_lineEdit_modif->setText(c.get_nomChercheur());
          ui->lineEdit_prenom_chercheur_Modif->setText(c.get_prenomChercheur());
          ui->lineEdit_email_chercheur_modif->setText(c.get_emailChercheur());
          ui->spinBox_age_chercheur_modif->setValue(c.get_ageChercheur());
          ui->lineEdit_telephone_chercheur_modif->setText(QString::number(c.get_telephoneChercheur()));
      } else {
          QMessageBox::critical(this, tr("Chercheur introuvable"),
              tr("Le chercheur avec l'ID %1 est introuvable.").arg(id_chercheur));
      }

   /* if (query.exec() && query.next()) {
        int cin = query.value("cin_chercheur").toInt();
        QString nom = query.value("nom_chercheur").toString();
        QString prenom = query.value("prenom_chercheur").toString();
        QString email= query.value("email_chercheur").toString();
        int age = query.value("age_chercheur").toInt();
        int telephone =query.value("telephone_chercheur").toInt();

        //int cin_chercheur= ui->lineEdit_cin_chercheur_modif->setPlaceholderText( cin );
        //QString nom_chercheur=ui->nom_cherchreur_lineEdit_modif->setPlaceholderText(nom);*/
        /*ui->lineEdit_cin_chercheur_modif->setPlaceholderText(QString::number(cin));
        ui->nom_cherchreur_lineEdit_modif->setPlaceholderText(nom);
        ui->lineEdit_prenom_chercheur_Modif->setPlaceholderText(prenom);
        ui->lineEdit_email_chercheur_modif->setPlaceholderText(email);
        ui->spinBox_age_chercheur_modif->setSpecialValueText(QString::number(age));
        ui->lineEdit_telephone_chercheur_modif->setPlaceholderText(QString::number(telephone));*/
       /* ui->lineEdit_cin_chercheur_modif->setText(QString::number(cin));
                ui->nom_cherchreur_lineEdit_modif->setText(nom);
                ui->lineEdit_prenom_chercheur_Modif->setText(prenom);
                ui->lineEdit_email_chercheur_modif->setText(email);
                ui->spinBox_age_chercheur_modif->setValue(age);
                ui->lineEdit_telephone_chercheur_modif->setText(QString::number(telephone));
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("modifier un chercheur"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }*/
//}

//void Dialog::on_pushButton_Modifier_2_clicked()
//{

//}
/*
void Dialog::on_pushButton_Modifier_2_clicked()
{
    int id_chercheur = ui->lineEdit_cin_chercheur_modif->text().toInt();


    int cin_chercheur = ui->lineEdit_cin_chercheur_modif->text().toInt();
     QString nom_chercheur= ui->nom_cherchreur_lineEdit_modif->text();
      QString prenom_chercheur= ui->lineEdit_prenom_chercheur_Modif->text();
      QString email_chercheur= ui->lineEdit_email_chercheur_modif->text();
      int telephone_chercheur= ui->lineEdit_telephone_chercheur_modif->text().toInt();
      int age_chercheur=ui->spinBox_age_chercheur_modif->text().toInt();
      Chercheurs c(cin_chercheur,nom_chercheur,prenom_chercheur,email_chercheur,telephone_chercheur,age_chercheur);
        Dialog *d= new Dialog();
       d->show();
      //d.exec();

      bool test=c.modifier(id_chercheur);

       if(test)
       {
            ui->tableView->setModel(C.afficher());
           QMessageBox::information(nullptr, QObject::tr("Modifier un chercheur"),
                       QObject::tr("Chercheur modifier.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);


       }
       else
           QMessageBox::critical(nullptr, QObject::tr("modifier un chercheur"),
                       QObject::tr("Erreur !.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);




}
*/
