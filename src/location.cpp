#include "location.h"

Location::Location(){
}

Location::Location(QString type, QString name, QString address, QString review)
    : location_type(type),location_name(name),location_address(address),location_review(review){
}

QString Location::get_type(){
    return this->location_type;
}

QString Location::get_name(){
    return this->location_name;
}

QString Location::get_address(){
    return this->location_address;
}

