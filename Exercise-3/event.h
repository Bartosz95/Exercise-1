#include <QListWidgetItem>
#ifndef EVENT_H
#define EVENT_H

class Event : public QListWidgetItem {

    public:
    int id;
    QString EventName;
    QDateTime EventDate;
    QTime EventTime;
    QTime EventAlarmReminder;
    QString EventPlace;
    QString EventNote;
    public:
    Event() : QListWidgetItem() {};
    Event(const QString & text, QListWidget * parent = 0, int type = Type) : QListWidgetItem(text,parent,type){};
};
#endif // EVENT_H
