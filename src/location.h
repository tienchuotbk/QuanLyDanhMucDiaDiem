#ifndef LOCATION_H
#define LOCATION_H
#include "list"
using namespace std;
#include <QString>
class Location
{
public:
    Location();
    Location(QString type, QString name, QString address,QString review);
    QString get_type();
    QString get_name();
    QString get_address();
    QString get_review();
private:
    QString location_type;
    QString location_name;
    QString location_address;
    QString location_review;

};

#endif // LOCATION_H
