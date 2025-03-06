#include "CCalendarMonth.h"
#include <iostream>
#include <cmath>
#include <set>

void CCalendarMonth::printCalendar(const string & date, const map<string, CEvent> &m) const{

    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    string firstDay = calculateDay(date);
    string sMonth = months[month - 1];

    cout << "\t\t\033[38;5;15;1m" << sMonth << endl;
    cout << "\tMo Tu We Th Fr Sa Sn" << endl;
    vector <int> monthDay {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    set <int> eventPrev;
    set <int> eventCur;
    set <int> eventNext;

    int prevMonth = month - 1;
    int nextMonth = month + 1;

    if (prevMonth == 0){
        prevMonth = 12;
    }
    if (nextMonth == 13){
        nextMonth = 1;
    }

    for (const auto &i: m){
        int monthNow = stoi(i.second.date.getDate().substr(3, 2));
        int yearNow = stoi(i.second.date.getDate().substr(6, 4));
        if (month == monthNow && (yearNow == year || i.second.frequency == "Annual")){
            int dayNow = stoi(i.second.date.getDate().substr(0, 2));
            eventCur.insert(dayNow);
        }
    }

    for (const auto &i: m){
        int monthNow = stoi(i.second.date.getDate().substr(3, 2));
        int yearNow = stoi(i.second.date.getDate().substr(6, 4));
        int yearPrev = year;
        if (prevMonth == 12){
            yearPrev--;
        }
        if (prevMonth == monthNow && (yearNow == yearPrev || i.second.frequency == "Annual")){
            int dayNow = stoi(i.second.date.getDate().substr(0, 2));
            eventPrev.insert(dayNow);
        }
    }

    for (const auto &i: m){
        int monthNow = stoi(i.second.date.getDate().substr(3, 2));
        int yearNow = stoi(i.second.date.getDate().substr(6, 4));
        int yearNext = year;
        if (nextMonth == 1){
            yearNext++;
        }
        if (nextMonth == monthNow && (yearNow == yearNext || i.second.frequency == "Annual")){
            int dayNow = stoi(i.second.date.getDate().substr(0, 2));
            eventNext.insert(dayNow);
        }
    }

    int prevCountDay = monthDay[prevMonth - 1];
    int nextCountDay = monthDay[nextMonth - 1];
    int countDay = monthDay[month - 1];

    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))){
        countDay++;
    }
    if (nextMonth == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))){
        nextCountDay++;
    }
    if (prevMonth == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))){
        prevCountDay++;
    }

    int counter = 1;
    int curDay = 0;
    auto it = weekDays.find(firstDay);
    int monthFirstDay = it->second;
    prevCountDay -= monthFirstDay - 2;
    cout << "\033[38;5;7;1m";

    cout << "\t";
        while (curDay < monthFirstDay - 1) {
            if (eventPrev.find(prevCountDay) != eventPrev.end()){
                cout << "\033[4m";
            }
            cout << prevCountDay;
            cout << "\033[0m\033[38;5;7;1m";
            prevCountDay++;
            curDay++;
            cout << " ";
            counter++;
        }
    cout << "\033[38;5;15;1m";
    int curDayWeek = 1;
    while (curDayWeek <= countDay){
        if (counter % 7 == 1 && counter != 1){
            cout << "\t";
        }
        if (curDayWeek < 10){
            cout << " ";
        }
        if (counter % 7 == 6 || counter % 7 == 0){
            cout << "\033[38;5;9;1m";
        }
        if (eventCur.find(curDayWeek) != eventCur.end()){
            cout << "\033[4m";
        }
        cout << curDayWeek;
        cout <<"\033[0m\033[38;5;15;1m";
        if (counter % 7 == 0 && (curDayWeek != countDay)){
            cout << endl;
        }
        cout << " ";
        curDayWeek++;
        counter++;
    }
    curDayWeek = 1;
    while (counter <= ceil(((double)(countDay - 1 + monthFirstDay) / 7)) * 7){
        if (counter % 7 == 6 || counter % 7 == 0){
            cout << "\033[38;5;204;1m";
        } else {
            cout << "\033[38;5;7;1m";
        }
        cout << " ";
        if (eventNext.find(curDayWeek) != eventNext.end()){
            cout << "\033[4m";
        }
        cout << curDayWeek;
        cout << "\033[0m\033[38;5;7;1m";
        cout << " ";
        curDayWeek++;
        counter++;
    }
    cout << endl << endl;
}
