#include "connection.h"

Connexion::Connexion()
{}

bool Connexion::ouvrirConnexion()
{
bool test=false;
    db=QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("Sana");
db.setPassword("esprit23");


if (db.open()) test = true;


return test;

}
void Connexion::fermerConnexion()
{db.close();}
