// Note we are only including time.h header. All the other required headers are declared in the actual time.h file
#include "time.h"

time::time(int hr, int min){
    setHour(hr);
    setMinute(min);
}

bool time::isLessThan(time other){
    return ( (hour < other.hour) || (hour == other.hour && minute < other.minute) );
}

void time::setHour(int newValue){
    if (newValue<1) hour = 1;
    else if (newValue > 12) hour =12;
    else hour = newValue;
}

void time::setMinute(int newValue){
    minute = newValue%60;
}

std::string time::toString(){
    return std::to_string(hour) + ":" + std::to_string(minute);
}

void time::shiftBy(int dh, int dm){
    this->hour+=dh;
    this->setMinute(minute+dm);
}

/*
void time::shiftBy(int dh, int dm){
    setHour(hour+dh);
    setMinute(minute+dh);
}
*/
