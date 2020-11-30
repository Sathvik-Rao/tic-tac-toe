#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <QInputDialog>
#include <QMessageBox>
#include <QMovie>
#include <QThread>
#include <QMouseEvent>

/*
Author - Sathvik Rao
June 2020
*/

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool closeAll = false;  //close all applications flag
    MainWindow(QWidget *parent = nullptr);
    void startGame();
    void gamePlayByPlayer();
    void gamePlayByComputer();
    void mousePressEvent(QMouseEvent *ev);
    void playAgain();
    ~MainWindow();

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

private:
   Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
