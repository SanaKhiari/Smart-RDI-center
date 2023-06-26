#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Chercheur.h"
#include<QStandardItemModel>
#include <QTableView>
#include <QMainWindow>
#include "ui_mainwindow.h"
#include"arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void on_pushButton_clicked();

    void on_Ajout_pushButton_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_Supprimer_clicked();

    void on_pushButton_Modifier_clicked();


    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();





    void on_pushButton_Export_clicked();

    void on_lineEdit_recherche_textChanged(const QString &arg1);

    void on_pushButton_Statistique_clicked();

    void on_pushButton_mailling_clicked();

    void on_help_button_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_Excel_clicked();

    void detectFlamme();

    //void on_pushButton_on_clicked();

   // void on_pushButton_of_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    Chercheurs C;
     arduino A;
};
#endif // MAINWINDOW_H
