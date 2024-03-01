#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_PB_AJOUTER_clicked();
    void on_BP_SPPRIMER_clicked();
    void on_pushButton_clicked();
private:
    Ui::MainWindow *ui;
    Client E;

};

#endif // MAINWINDOW_H
