#include "mainwindow.h"
#include "connection.h"
#include <QSqlDatabase>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   Connexion c;
   bool test= c.ouvrirConnexion();
   MainWindow w;
              if(test)
{
        w.show();


    }
          else
               QMessageBox::information(nullptr, QObject::tr("database is not open"),
                           QObject::tr("Echec de la connexion.\n""Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
