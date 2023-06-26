#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "connection.h"
#include"Chercheur.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QStandardItemModel>
#include <QTableView>
#include "mainwindow.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void Mcher(int);
    void afficherD(int);

private slots:

  //  void on_pushButton_Modifier_2_clicked();


    void on_pushButton_Modifier_2_clicked();

private:
    Ui::Dialog *ui;
     Chercheurs C;

};

#endif // DIALOG_H
