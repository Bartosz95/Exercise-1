#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
 ui->setupUi(this);
 ui->stackedWidget->setCurrentWidget(ui->PageCallender);
 mode=0;
    try  {
        setDatabaseConfig();
        getDayEvent(ui->calendarWidget->selectedDate());

    } catch (QString &e) {
        errorMessageBox(e);
        exit(0);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//------public funcion------//

void MainWindow::setDatabaseConfig(){
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("kalendarz");
}

void MainWindow::getDayEvent(const QDate &date){
    try{
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        if(db.open()){
            mysqlquery.prepare("SELECT * FROM wydarzenia WHERE czas BETWEEN :sdate1 AND :sdate2 ORDER BY czas ASC");
            mysqlquery.bindValue(":sdate1",date.toString("yyyy-MM-dd"));
            mysqlquery.bindValue(":sdate2",date.addDays(1).toString("yyyy-MM-dd"));
            if(mysqlquery.exec()){
                ui->ListWidgetEvent->clear();
                Eventlist.clear();
                if(mysqlquery.size()>0){
                    while(mysqlquery.next()){
                        Event *ew= new Event();
                        ew->id=mysqlquery.value("id").toInt();
                        ew->EventName=mysqlquery.value("nazwa").toString().toUtf8().constData();
                        ew->EventDate=mysqlquery.value("czas").toDateTime();
                        ew->EventTime=mysqlquery.value("dlugosc").toTime();
                        ew->EventAlarmReminder=mysqlquery.value("alarm").toTime();
                        ew->EventPlace=mysqlquery.value("miejsce").toString().toUtf8().constData();
                        ew->EventNote=mysqlquery.value("notatka").toString().toUtf8().constData();
                        Eventlist.push_back(ew);
                        ew->setText(ew->EventDate.toString("hh:mm:ss")+" | "+ew->EventName);
                        ui->ListWidgetEvent->addItem(Eventlist.back());
                   }
                }else{
                    qDebug() << "No events";
                }
            }else{
                throw QObject::tr("something went wrong");
            }
        db.close();
        }else{
           throw QObject::tr("Error Database Connect");
        }
    }catch (QString &e) {
        errorMessageBox(e);
    }
}

void MainWindow::insertDatabaseEvent(Event *ew){
    if(db.open()){
       mysqlquery.prepare("INSERT INTO wydarzenia (id, nazwa, czas, dlugosc, alarm, miejsce, notatka) "
                          "VALUES (NULL, :nazwa, :czas, :dlugosc, :alarm, :miejsce, :notatka)");
       mysqlquery.bindValue(":nazwa",ew->EventName);
       mysqlquery.bindValue(":czas",ew->EventDate.toString("yyyy-MM-dd HH:mm:ss"));
       mysqlquery.bindValue(":dlugosc",ew->EventTime.toString("HH:mm:ss"));
       mysqlquery.bindValue(":alarm",ew->EventAlarmReminder.toString("HH:mm:ss"));
       mysqlquery.bindValue(":miejsce",ew->EventPlace);
       mysqlquery.bindValue(":notatka",ew->EventNote);
       if(mysqlquery.exec()){
            errorMessageBox(QObject::tr("Good added event!"));
       } else {
            throw QObject::tr("something went wrong");
       }
      db.close();
    }else{
        throw QObject::tr("Error Database connection");
    }
}

void MainWindow::updateDatabaseEvent(Event*ew){
    if(db.open()){
       mysqlquery.prepare("UPDATE wydarzenia SET nazwa=:upnazwa, czas=:upczas, dlugosc=:updlugosc,"
                          " alarm=:upalarm, miejsce=:upmiejsce, notatka=:upnotatka WHERE id=:upid ");
       mysqlquery.bindValue(":upid",ew->id);
       mysqlquery.bindValue(":upnazwa",ew->EventName);
       mysqlquery.bindValue(":upczas",ew->EventDate.toString("yyyy-MM-dd HH:mm:ss"));
       mysqlquery.bindValue(":updlugosc",ew->EventTime.toString("HH:mm:ss"));
       mysqlquery.bindValue(":upalarm",ew->EventAlarmReminder.toString("HH:mm:ss"));
       mysqlquery.bindValue(":upmiejsce",ew->EventPlace);
       mysqlquery.bindValue(":upnotatka",ew->EventNote);
       if(mysqlquery.exec()){
            errorMessageBox(QObject::tr("Good change value"));
       } else {
            throw QObject::tr("something went wrong");
       }
      db.close();
    }else{
        throw QObject::tr("Error Database connection");
    }
}

void MainWindow::deleteDatabaseEvent(Event *ew){
    if(db.open()){
        mysqlquery.prepare("DELETE FROM wydarzenia WHERE id = :delid");
        mysqlquery.bindValue(":delid",ew->id);
        if(mysqlquery.exec()){
            errorMessageBox(QObject::tr("Good delete event"));
            this->getDayEvent(ui->WDataTime->date());
        } else {
           throw QObject::tr("Error Database connection");
        }
    db.close();
    }
}

int MainWindow::getClickedEvent(){
    if(ui->ListWidgetEvent->row(ui->ListWidgetEvent->currentItem())>=0){
        QString nazwa = ui->ListWidgetEvent->currentItem()->text();
        for (int i=0;i<Eventlist.size();i++){
            if((Eventlist[i]->EventDate.toString("hh:mm:ss")+" | "+Eventlist[i]->EventName)==nazwa){
                return i;
            }
        }
    }else{
       throw QObject::tr("No selected event");
    }
    return 0;
}

void MainWindow::errorMessageBox(QString errorString)const{
    QMessageBox *msgBox = new QMessageBox;
    msgBox->setWindowTitle(QObject::tr("INFO"));
    msgBox->setInformativeText(errorString);
    QAbstractButton* ButtonYes = msgBox->addButton(QObject::tr("OK"), QMessageBox::YesRole);
    msgBox->exec();
    if (msgBox->clickedButton() == ButtonYes) {}
}

//------private slots------//
void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    this->getDayEvent(date);
}

void MainWindow::on_BOK_accepted()
{
    try{
        Event *ew= new Event;
        ew->EventName=ui->WName->text();
        ew->EventDate=ui->WDataTime->dateTime();
        ew->EventTime=ui->WDuration->time();
        ew->EventAlarmReminder=ui->WAlarm->time();
        ew->EventPlace=ui->WLocation->text();
        ew->EventNote=ui->WNote->text();
        if(mode==1){
          insertDatabaseEvent(ew);
        }else if(mode==2){
          ew->id=this->id;
          updateDatabaseEvent(ew);
        }else{
            throw QObject::tr("Wrong mode");
        }
        ui->stackedWidget->setCurrentWidget(ui->PageCallender);
        this->getDayEvent(ui->WDataTime->date());
    }catch (QString &e) {
        errorMessageBox(e);
    }
}

void MainWindow::on_BOK_rejected()
{
    ui->stackedWidget->setCurrentWidget(ui->PageCallender);
}

void MainWindow::on_pushButton_clicked()
{
   try{
      int i=getClickedEvent();
       QMessageBox *msgBox = new QMessageBox;
       msgBox->setWindowTitle(QObject::tr("DELETE"));
       msgBox->setInformativeText(QObject::tr("Do you wont delete a event: ")+Eventlist[i]->EventName+" ?");
       QAbstractButton* ButtonNo = msgBox->addButton(tr("Back"),QMessageBox::NoRole);
       QAbstractButton* ButtonYes = msgBox->addButton(tr("Delete event"), QMessageBox::YesRole);
       msgBox->exec();
       if (msgBox->clickedButton() == ButtonYes) {
           deleteDatabaseEvent(Eventlist[i]);
       }else if (msgBox->clickedButton() == ButtonNo) {
       }
       delete msgBox;
   }catch(QString &e){
        errorMessageBox(e);
   }
}

void MainWindow::on_pushButton_2_clicked()
{
    try  {
        int i=getClickedEvent();
        this->id=Eventlist[i]->id;
        ui->WName->setText(Eventlist[i]->EventName);
        ui->WDataTime->setDateTime(Eventlist[i]->EventDate);
        ui->WAlarm->setTime(Eventlist[i]->EventAlarmReminder);
        ui->WDuration->setTime(Eventlist[i]->EventTime);
        ui->WLocation->setText(Eventlist[i]->EventPlace);
        ui->WNote->setText(Eventlist[i]->EventNote);
        ui->stackedWidget->setCurrentWidget(ui->PageAddEvent);
        mode=2;
    } catch (QString &e) {
        errorMessageBox(e);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QDateTime data(ui->calendarWidget->selectedDate());
    QTime time(9,0,0);
    data.setTime(time);
    ui->WDataTime->setDateTime(data);
    time = QTime::fromString("00:30", "hh:mm");
    ui->WAlarm->setTime(time);
    time = QTime::fromString("02:00", "hh:mm");
    ui->WDuration->setTime(time);
    this->mode=1;
    ui->stackedWidget->setCurrentWidget(ui->PageAddEvent);
}

void MainWindow::on_ListWidgetEvent_clicked(const QModelIndex &index)
{
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
}
