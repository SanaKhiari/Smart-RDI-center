#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include "notif.h"
#include "Chercheur.h"
#include <QMessageBox>
#include <QSqlQuery>


#include <QPixmap>
#include<iostream>
#include <QPainter>
#include <QFileDialog>
#include <QPdfWriter>
#include <QTextDocument>
#include <QSqlRecord>
#include <QTextDocument>
#include <QPdfWriter>

#include <QSqlRecord>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include <QPrinter>
#include <QPrintDialog>

//#include <curl/curl.h>
#include"SmtpMime"
#include <QShortcut>

#include <QTextStream>
#include "arduino.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //controle de saisie :
    ui->tableView->setModel(C.afficher());
    ui->tableView_historique->setModel(C.afficher_historique());
    ui->lineEdit_cin_chercheur -> setValidator (new QIntValidator(0, 999999999, this));
    ui->lineEdit_telephone_chercheur -> setValidator (new QIntValidator(0, 999999999, this));
    ui->lineEdit_cin_modifierOuSupprimer -> setValidator (new QIntValidator(0, 999999, this));
    //ui->nom_chrchreur_lineEdit->setInputMask("aaaaaaaaaa");
    //ui->lineEdit_prenom_chercheur->setInputMask("aaaaaaaaaa");
    ui->nom_chrchreur_lineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]+"), this));
    ui->lineEdit_prenom_chercheur->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]+"), this));
    ui->lineEdit_email_chercheur->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9.]+@[a-zA-Z]+\\.[a-zA-Z]{,5}"), this));
    ui->lineEdit_adress_recep->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9.]+@[a-zA-Z]+\\.[a-zA-Z]{,5}"), this));

   ui->lineEdit_recherche->setPlaceholderText("Enterer le nom du chercheur ici...");
   ui->lineEdit_adress_recep->setPlaceholderText("adresse mail à qui envoyer...");
   ui->lineEdit_subject->setPlaceholderText("sujet...");
   ui->plainTextEdit_mailText->setPlaceholderText("ecrivez votre mail ici...");



    /*QPixmap bkgnd("C:/Users/21624/Documents/C++/backgroundDesktop.png");
        bkgnd=bkgnd.scaled(this->size(),Qt::IgnoreAspectRatio);
        QPalette p;
        p.setBrush(QPalette::Background, bkgnd);
        this->setPalette(p);
*/

      //  model=new QStandardItemModel(7,7,this);
                   // model->setHorizontalHeaderLabels({"ID_chercheur ","CIN_chercheur","Nom ","Prénom","age","téléphone","email",});

                      // ATTENTION tu dois aussi le definir comme pointeur dans ton .h
                      // pour les lignes
                     /* for (int i=0;i<7;++i)
                        { // Pour les colonnes
                        for (int j=0;j<7;++j)
                          {  // on crée un item==cellule
                           QStandardItem *item = new QStandardItem;
                           // On définit les valeurs initiales des cases
                           //item->setText("") ;
                           //item->setText(QString::number(0));
                           // Et enfin on l'associe avec notre model

                           model->setItem(0,0,item);
                          }
                        }
                        //recuperer les valeurs :
                           // int valeur = model->item(ligne, colonne)->text().toInt();
                           // double valeur = model->item(ligne, colonne)->text().toDouble();

                      // affichage, on utilise un QTableView

                      ui->tableView->setModel(model);

*/

   //shortcuts

   //**ajout
   QShortcut* shortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_A), this);
   connect(shortcut, &QShortcut::activated, this, &MainWindow::on_Ajout_pushButton_clicked);
   //**supprimer
   QShortcut* shortcut1 = new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_D), this);
   connect(shortcut1, &QShortcut::activated, this, &MainWindow::on_pushButton_Supprimer_clicked);
   //**modifier
   QShortcut* shortcut2 = new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_M), this);
   connect(shortcut2, &QShortcut::activated, this, &MainWindow::on_pushButton_Modifier_clicked);
   //**reset
   QShortcut* shortcut3 = new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_R), this);
   connect(shortcut3, &QShortcut::activated, this, &MainWindow::on_pushButton_reset_clicked);
    //**statstique
   QShortcut* shortcut4 = new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S), this);
   connect(shortcut4, &QShortcut::activated, this, &MainWindow::on_pushButton_Statistique_clicked);
   //**pdf
   QShortcut* shortcut5 = new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_P), this);
   connect(shortcut5, &QShortcut::activated, this, &MainWindow::on_pushButton_Export_clicked);
    //**trier
   QShortcut* shortcut6 = new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_T), this);
   connect(shortcut6, &QShortcut::activated, this, &MainWindow::on_pushButton_20_clicked);
    //**mailling
   QShortcut* shortcut7 = new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_E), this);
   connect(shortcut7, &QShortcut::activated, this, &MainWindow::on_pushButton_mailling_clicked);
    //**Documentation
   QShortcut* shortcut8 = new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_H), this);
   connect(shortcut8, &QShortcut::activated, this, &MainWindow::on_help_button_clicked);
    //**Quiter cette interface
   QShortcut* shortcut9 = new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Q), this);
   connect(shortcut9, &QShortcut::activated, this, &MainWindow::close);


   //arduino:::

     int ret=A.connect_arduino(); // lancer la connexion & arduino
     switch (ret){
      case (0):qDebug ()<< "arduino is available and connected to :"<<A.getarduino_port_name();
          break;
      case (1) : qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
         break;
      case (-1) :qDebug () << "arduino is not available";
      }

     QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(detectFlamme()));
     //QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(on_pushButton_on_clicked()));
     //QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(on_pushButton_of_clicked()));



   //*****
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::detectFlamme(){
    QByteArray data;
    data = A.read_from_arduino();

    QString strData = QString::fromUtf8(data);
    if(strData=="1"){

        SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

        // We need to set the username (your email address) and the password
        // for smtp authentification.

        smtp.setUser("sana.khiari@esprit.tn");
        smtp.setPassword("");//password of your email

        
        // Now we create a MimeMessage object. This will be the email.

        MimeMessage message;

        message.setSender(new EmailAddress("sana.khiari@esprit.tn", "dynamic discoveries "));
        message.addRecipient(new EmailAddress("sana.khiari2002@gmail.com", "Recipient's Name"));

        message.setSubject("Incendi");


        // Now add some text to the email.
        // First we create a MimeText object.

        MimeText text;

        text.setText("Hi,\n in SMART RDI center there is fire detected.\n");

        // Now add it to the mail

        message.addPart(&text);

        // Now we can send the mail

        smtp.connectToHost();
        smtp.login();
        if(smtp.sendMail(message)){
           // QMessageBox::information(this,"ok","email envoyer");
            //notif m("Chercheur","Smart rdi center a envoyé un email");
            //m.afficher();

            //bool test2= C.ajouter_historique("Un email est envoyé");
             //ui->tableView_historique->setModel(C.afficher_historique());
        }else{
            //QMessageBox::information(this,"ok","email non envoyer");
            //notif m("Chercheur","Smart rdi center n'a pas  envoyé un email");
            //m.afficher();
        }
        smtp.quit();



    bool test2= C.ajouter_historique("Fire detected");
    ui->tableView_historique->setModel(C.afficher_historique());
    notif m("Chercheur","there is fire in SMART RDI Center");
    m.afficher();

    }
}



void MainWindow::on_Ajout_pushButton_clicked()
{
    //int id_chercheur = ui->lineEdit_id_chercheur->text().toInt();
    int cin_chercheur = ui->lineEdit_cin_chercheur->text().toInt();
        QString nom_chercheur= ui->nom_chrchreur_lineEdit->text();
        QString prenom_chercheur= ui->lineEdit_prenom_chercheur->text();
        QString email_chercheur= ui->lineEdit_email_chercheur->text();
        int telephone_chercheur= ui->lineEdit_telephone_chercheur->text().toInt();
        int age_chercheur=ui->spinBox_age_chercheur->text().toInt();

      Chercheurs c(cin_chercheur,nom_chercheur,prenom_chercheur,email_chercheur,telephone_chercheur,age_chercheur);
      if(!C.trouverChercheurByCin(cin_chercheur)){
      bool test=c.ajouter();
      if(test)
      {
          notif m("Chercheur","Chercheur Ajouter");
          m.afficher();

          bool test2= C.ajouter_historique("Chercheur ajoute");
         ui->tableView->setModel(c.afficher());
         ui->tableView_historique->setModel(C.afficher_historique());
      QMessageBox::information(nullptr, QObject::tr("Ajouter un Chercheur"),
                        QObject::tr("chercheurs ajoutes.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

      }
        else
            QMessageBox::critical(nullptr, QObject::tr("Ajouter un chercheur"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
      }else{
          QMessageBox::critical(nullptr, QObject::tr("Ajouter un chercheur"),
                      QObject::tr("Erreur le cin du chercheur existe deja"
                                  "il faut entrer un autre cin  !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
      }


}

void MainWindow::on_pushButton_reset_clicked()
{
            ui->lineEdit_cin_chercheur->clear();
            ui->nom_chrchreur_lineEdit->clear();
            ui->lineEdit_prenom_chercheur->clear();
            ui->lineEdit_email_chercheur->clear();
            ui->lineEdit_telephone_chercheur->clear();
            ui->spinBox_age_chercheur->clear();
            notif m("Chercheur","Vous avez effacer tous les champs remplies");
            m.afficher();
}

void MainWindow::on_pushButton_Supprimer_clicked()
{

    int cin_chercheur = ui->lineEdit_cin_modifierOuSupprimer->text().toInt();

    if(C.trouverChercheurById(cin_chercheur)){
    bool test=C.supprimer(cin_chercheur);
    if(test)
    {
        bool test2= C.ajouter_historique("Chercheur suprimer");
         ui->tableView_historique->setModel(C.afficher_historique());
        notif m("Chercheur","Chercheur Suprimer");
        m.afficher();

        ui->tableView->setModel(C.afficher());
        QMessageBox::information(nullptr, QObject::tr("Supprimer un chercheur"),
                    QObject::tr("Chercheur supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un chercheur"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un chercheur"),
                    QObject::tr("Erreur le chercheur n'existe pas !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_Modifier_clicked()
{

    int id_chercheur = ui->lineEdit_cin_modifierOuSupprimer->text().toInt();

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    int cin_chercheur = ui->lineEdit_cin_chercheur->text().toInt();
     QString nom_chercheur= ui->nom_chrchreur_lineEdit->text();
      QString prenom_chercheur= ui->lineEdit_prenom_chercheur->text();
      QString email_chercheur= ui->lineEdit_email_chercheur->text();
      int telephone_chercheur= ui->lineEdit_telephone_chercheur->text().toInt();
      int age_chercheur=ui->spinBox_age_chercheur->text().toInt();
      Chercheurs c(cin_chercheur,nom_chercheur,prenom_chercheur,email_chercheur,telephone_chercheur,age_chercheur);
        //Dialog *d= new Dialog();
      // d->show();
      //d.exec();
    if(c.trouverChercheurById(id_chercheur)){
      bool test=c.modifier(id_chercheur);

       if(test)
       {
           notif m("Chercheur","Chercheur Modifier");
           m.afficher();
           bool test2= C.ajouter_historique("Chercheur Modifier");
            ui->tableView_historique->setModel(C.afficher_historique());

            ui->tableView->setModel(C.afficher());
           QMessageBox::information(nullptr, QObject::tr("Modifier un chercheur"),
                       QObject::tr("Chercheur modifier.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);


       }
       else{
           QMessageBox::critical(nullptr, QObject::tr("modifier un chercheur"),
                       QObject::tr("Erreur !.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
       }
}else{
       QMessageBox::critical(nullptr, QObject::tr("modifier un chercheur"),
                QObject::tr("Erreur chercheur introuvable!.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);

       }
}


void MainWindow::on_pushButton_19_clicked()
{


    QString nom_chercheur = ui->lineEdit_recherche->text();
    //QSqlQueryModel* model = C.rechercher(nom_chercheur);
    ui->tableView->setModel(C.rechercher(nom_chercheur));




}

void MainWindow::on_pushButton_20_clicked()
{

           Chercheurs a;
           if (ui->checkBox->isChecked() && ui->checkBox_2->isChecked()) {
                          QMessageBox::information(nullptr, QObject::tr("Chercher un chercheur"),
                                      QObject::tr("Erreur.\n"
                                                  "S'il vous plaît choisir un seul ordre."), QMessageBox::Cancel);
                      }
           else if(ui->checkBox->isChecked()){
                ui->tableView->setModel(C.trier());



                notif m("Chercheurs","Liste des Chercheurs est trier dans l'ordre croissant");
                m.afficher();
                bool test2= C.ajouter_historique("listes des chercheurs etait trier dans un ordre croissant");
                 ui->tableView_historique->setModel(C.afficher_historique());


           }else if(ui->checkBox_2->isChecked()){
               ui->tableView->setModel(C.trierDec());

               notif m("Chercheurs","Liste des Chercheurs est trier dans l'ordre décroissant");
               m.afficher();

               bool test2= C.ajouter_historique("listes des chercheurs etait trier dans un ordre decroissant");
                ui->tableView_historique->setModel(C.afficher_historique());
           }
           else{
               QMessageBox::information(nullptr, QObject::tr("Chercher un chercheur"),
                           QObject::tr("Erreur .\n"
                                       "S'il vous plait choisissez un ordre .\n"
                                       "Voulez-vous un ordre croissant ou bien decroissant ?"), QMessageBox::Cancel);

           }



}



void MainWindow::on_pushButton_Export_clicked()
{
        QString strStream;
        QTextStream out(&strStream);

        const int rowCount = ui->tableView->model()->rowCount();
        const int columnCount = ui->tableView->model()->columnCount();

        out << "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            "<title>Liste Des Chercheurs</title>\n"
            "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"
            "<img src=\"C:/Users/21624/Documents/cher/logoSmartRdiCenter.png\" width=\"100\" height=\"100\">"
            "<center><H1>Dynamic Discoveries (Smart RDI center)<H1></center>"
            "<center><H2>Liste Des Chercheurs</H2></center>\n"
            "<table border=1 cellspacing=0 cellpadding=2>\n";

        // headers
        out << "<thead><tr bgcolor=#f0f0f0><th>Numero</th>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView->isColumnHidden(column))
            {
                QString header = ui->tableView->model()->headerData(column, Qt::Horizontal).toString();
                out << QString("<th>%1</th>").arg(header);
            }
        }
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++)
        {
            out << "<tr><td bkcolor=0>" << row + 1 << "</td>";
            for (int column = 0; column < columnCount; column++)
            {
                if (!ui->tableView->isColumnHidden(column))
                {
                    QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                    out << QString("<td bkcolor=0>%1</td>").arg(data.isEmpty() ? "&nbsp;" : data);
                }
            }
            out << "</tr>\n";
        }
        out << "</table>\n"
            "</body>\n"
            "</html>\n";

        QString fileName = QFileDialog::getSaveFileName(this, tr("Sauvegarder en PDF"), QString(), tr("PDF files (*.pdf)"));
        if (!fileName.isEmpty())
        {
            if (QFileInfo(fileName).suffix().isEmpty())
            {
                fileName.append(".pdf");
            }

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setPaperSize(QPrinter::A4);
            printer.setOutputFileName(fileName);

            QTextDocument doc;
            doc.setHtml(strStream);
            doc.setPageSize(printer.pageRect().size());
            doc.print(&printer);
        }

        notif m("Pdf","Liste des Chercheurs est exporter en pdf sur votre ordinateur");
        m.afficher();
        bool test2= C.ajouter_historique("la listes des chercheurs est exporté en PDF");
         ui->tableView_historique->setModel(C.afficher_historique());



}

void MainWindow::on_lineEdit_recherche_textChanged(const QString &arg1)
{
    QString nom_chercheur = ui->lineEdit_recherche->text();
    //QSqlQueryModel* model = C.rechercher(nom_chercheur);
    ui->tableView->setModel(C.rechercher(nom_chercheur));

    bool test2= C.ajouter_historique("il y a une recherche");
     ui->tableView_historique->setModel(C.afficher_historique());
}

void MainWindow::on_pushButton_Statistique_clicked()
{
    bool test2= C.ajouter_historique("generation d'une statistique");
     ui->tableView_historique->setModel(C.afficher_historique());

    C.genererStatistique();
    notif m("Chercheurs","La gestion des chercheurs a génerer staistique d'age");
    m.afficher();


}

void MainWindow::on_pushButton_mailling_clicked()
{

     QString mail_recep= ui->lineEdit_adress_recep->text();
     QString mail_subject= ui->lineEdit_subject->text();
     QString mail_text= ui->plainTextEdit_mailText->toPlainText();
    // This is a first demo application of the SmtpClient for Qt project

    // First we need to create an SmtpClient object
    // We will use the Gmail's smtp server (smtp.gmail.com, port 465, ssl)

    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

    // We need to set the username (your email address) and the password
    // for smtp authentification.

    smtp.setUser("sana.khiari@esprit.tn");
    smtp.setPassword("xxxpekkifbyyijfx");

    // Now we create a MimeMessage object. This will be the email.

    MimeMessage message;

    message.setSender(new EmailAddress("sana.khiari@esprit.tn", "dynamic discoveries "));
    //message.addRecipient(new EmailAddress("sana.khiari2002@gmail.com", "Recipient's Name"));
    message.addRecipient(new EmailAddress(mail_recep, "Recipient's Name"));
    //message.setSubject("SmtpClient for Qt - Demo");
    message.setSubject(mail_subject);

    // Now add some text to the email.
    // First we create a MimeText object.

    MimeText text;

    //text.setText("Hi,\nThis is a simple email message.\n");
    text.setText(mail_text);
    // Now add it to the mail

    message.addPart(&text);

    // Now we can send the mail

    smtp.connectToHost();
    smtp.login();
    if(smtp.sendMail(message)){
        QMessageBox::information(this,"ok","email envoyer");
        notif m("Chercheur","Smart rdi center a envoyé un email");
        m.afficher();

        bool test2= C.ajouter_historique("Un email est envoyé");
         ui->tableView_historique->setModel(C.afficher_historique());
    }else{
        QMessageBox::information(this,"ok","email non envoyer");
        notif m("Chercheur","Smart rdi center n'a pas  envoyé un email");
        m.afficher();
    }
    smtp.quit();




}


void MainWindow::on_help_button_clicked()
{
//    QString filePath = QFileDialog::getOpenFileName(this, tr("Import File"), QDir::homePath(), tr("Text files (*.txt)"));
    QString filePath = "C:\\Users\\21624\\Documents\\cher\\help.txt";

        if (!filePath.isEmpty()) {
            QFile file(filePath);

            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QString contents = in.readAll();
                ui->textEdit->setText(contents);
                file.close();
            } else {
                qDebug() << "Failed to open file for reading: " << file.errorString();
            }
        }
        notif m("Chercheur","Une documentation est afficher");
        m.afficher();
}


void MainWindow::on_pushButton_24_clicked()
{
    bool t=C.supprimer_historique();
    ui->tableView_historique->setModel(C.afficher_historique());
}

void MainWindow::on_pushButton_Excel_clicked()
{
    QFile file("C:/Users/21624/Documents/cher/excel.csv");
                      QSqlQueryModel* model=new QSqlQueryModel();
                      model->setQuery("SELECT* FROM  CHERCHEURS");

                      if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                          QTextStream data(&file);
                          QStringList strList;
                          for (int i = 0; i < model->columnCount(); i++) {
                              if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                                  strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                              else
                                  strList.append("");
                          }
                          data << strList.join(";") << "\n";
                          for (int i = 0; i < model->rowCount(); i++) {
                              strList.clear();
                              for (int j = 0; j < model->columnCount(); j++) {

                                  if (model->data(model->index(i, j)).toString().length() > 0)
                                      strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                                  else
                                      strList.append("");
                              }
                              data << strList.join(";") + "\n";
                          }
                          file.close();

                      }

                      bool test2= C.ajouter_historique("listes des chercheurs est exporter en excel");
                       ui->tableView_historique->setModel(C.afficher_historique());
                       notif m("Chercheur","Un execel est exporté");
                       m.afficher();

}
/*
void MainWindow::on_pushButton_on_clicked()
{
    //A.write_to_arduino(QByteArray("1")); //envoyer 1 à arduino
    notif m("Chercheur","1 est envoyer");
    m.afficher();

}

void MainWindow::on_pushButton_of_clicked()
{
   // A.write_to_arduino(QByteArray("0")); //envoyer 0 à arduino
    notif m("Chercheur","0 est envoyer");
    m.afficher();

}
*/
