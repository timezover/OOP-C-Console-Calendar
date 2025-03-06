#include "CTime.h"
#include "CCommand.h"
#include <iostream>

void splitTime(const string & time, int & hours, int & min){
    size_t pos = time.find(':');
    hours = stoi(time.substr(0, pos));
    min = stoi(time.substr(pos + 1));
}

string CTime::getTime() const{
    return time;
}

void CTime::setAttr(const string & newAttr){
    time = newAttr;
}

CTime::CTime(const string & t){
    time = t;
}

bool CTime::timeValid(){
    if (time.length() != 5){
        return false;
    }
    if (time[2] != ':'){
        return false;
    }
    for (int i = 0; i < 4; i++){
        if ((time[i] < '0' || time[i] > '9') && i != 2)
            return false;
    }
    int hour = stoi(time.substr(0, 2));
    int minute = stoi(time.substr(3, 2));

    if (hour > 24 || minute > 59){
        return false;
    }

    return true;
}

bool checkOrder(const string & startTime, const string & endTime){
    int hoursStart, hoursEnd;
    int minutesStart, minutesEnd;

    splitTime(startTime, hoursStart, minutesStart);
    splitTime(endTime, hoursEnd, minutesEnd);

    if (hoursStart > hoursEnd || (hoursStart == hoursEnd && minutesStart > minutesEnd)){
        return false;
    }

    return true;
}

void CTime::inputAttr(const string & str){
    while ( true ){
        string time_;
        cout << "\t\033[38;5;14;1m>>\033[0m ";
        cout << "\033[38;5;231;1m";
        getline(cin, time_);
        if (cin.eof()) {
            throw runtime_error("EOF reached while executing command");
        }
        removeSpace(time_);
        CTime t(time_);
        if (t.timeValid() || time_.empty()){
            setAttr(time_);
            break;
        } else {
            cout << "\033[38;5;14;1m~ Invalid time format. Write " << str << " time of the event in format HH:MM" << endl;
        }
    }
}

ostream& operator<<(std::ostream& os, const CTime &obj) {
    return os << obj.time;
}

bool CTime::empty() const{
    return time.empty();
}