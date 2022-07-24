#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QString>
#include <QDate>
#include <QDateTime>
#include <QUnhandledException>
#include <QList>
#include <QListWidget>
#include <QCalendarWidget>
#include <QMessageBox>
#include <iostream>

#include "event.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setDatabaseConfig();

    void getDayEvent(const QDate &date);

    void insertEvent();

    void insertDatabaseEvent(Event*);

    void updateDatabaseEvent(Event*);

    void deleteDatabaseEvent(Event*);

    int getClickedEvent();

    void errorMessageBox(QString )const;

private slots:

    void on_calendarWidget_clicked(const QDate &date);

    void on_BOK_accepted();

    void on_BOK_rejected();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_ListWidgetEvent_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    QListWidget *listWidget;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    QList<Event*> Eventlist;

    QSqlQuery mysqlquery;

    int mode , id;
};

#endif // MAINWINDOW_H
