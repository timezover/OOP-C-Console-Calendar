#include "CDate.h"
#include "CCommand.h"
#include <vector>
#include <iostream>

string calculateDay(const string & s){
    string weekDay;
    int day = stoi(s.substr(0, 2));
    int month = stoi(s.substr(3, 2));
    int year = stoi(s.substr(6, 4));
    vector <string> days = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    tm timeIn = {0, 0, 0, day, month - 1, year - 1900};
    time_t timeTemp = mktime(&timeIn);
    const tm* timeOut = localtime(&timeTemp);

    return days[timeOut->tm_wday];
}

void CDate::setAttr(const string &newAttr){
    date = newAttr;
}

bool CDate::empty() const{
    return date.empty();
}

string CDate::getDate() const{
    return date;
}

ostream & operator<<(std::ostream& os, const CDate &obj){
    return os << obj.date;
}

void CDate::inputAttr(const string & str){
    if (str == "Annual"){
        cout << "\033[38;5;14;1m~ Write the date of the event in format DD.MM" << endl;
    } else {
        cout << "\033[38;5;14;1m~ Write the date of the event in format DD.MM.YYYY" << endl;
    }
    string dateIn;
    while ( true ) {
        cout << "\t\033[38;5;14;1m>>\033[0m ";
        cout << "\033[38;5;231;1m";
        getline(cin, dateIn);
        if (cin.eof()) {
            throw runtime_error("EOF reached while executing command");
        }
        removeSpace(dateIn);
        string dateCheck = dateIn;

        if (str == "Annual"){
            dateIn += ".2001";
        }

        if (dateValid(dateIn)){
            break;
        } else if (dateCheck == "") {
            cout << "\033[38;5;14;1m~ This field is necessary. Write the date in format ";
            if (str == "Annual"){
                cout << "DD.MM" << endl;
            } else {
                cout << "DD.MM.YYYY" << endl;
            }
        } else {
            if (str == "Annual"){
                cout << "\033[38;5;14;1m~ Invalid date format or year is not in range 2000-2100. Write the date of the event in format DD.MM:" << endl;
            } else {
                cout << "\033[38;5;14;1m~ Invalid date format or year is not in range 2000-2100. Write the date of the event in format DD.MM.YYYY:" << endl;
            }
        }
    }
    setAttr(dateIn);
}


bool dateValid(const string & date){
    if (date.length() != 10) {
        return false;
    }
    if (date[2] != '.' || date[5] != '.'){
        return false;
    }
    for (int i = 0; i < 10; i++){
        if ((date[i] < '0' || date[i] > '9') && i != 2 && i != 5){
            return false;
        }
    }
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (year < 2000 || year > 2100){
        return false;
    }

    if (day < 1 || day > 31 || month < 1 || month > 12){
        return false;
    }

    bool leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if ((month == 2 && day > 28 + leapYear) || ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)) {
        return false;
    }

    return true;
}