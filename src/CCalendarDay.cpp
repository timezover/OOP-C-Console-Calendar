#include "CCalendarDay.h"
#include "CInterface.h"
#include <iostream>

void CCalendarDay::printCalendar(const string & date, const map <string, CEvent> & m) const{
    cout << "\033[38;5;49;1m~ Write the day in format DD.MM.YYYY" << endl;
    string s;
    removeSpace(s);
    while ( true ) {
        cout << "\t>> \033[38;5;15;1m";
        getline(cin, s);
        if (cin.eof()) {
            throw runtime_error("EOF reached while executing command");
        }
        removeSpace(s);
        if (dateValid(s)){
            break;
        } else {
            cout << "\033[38;5;49;1m~ Invalid format or year is not in range 2000-2100. Write the day in format DD:MM:YYYY" << endl;
        }
    }
    cout << endl;
    int day = stoi(s.substr(0, 2));
    int month = stoi(s.substr(3, 2));
    string dayWeek = calculateDay(s);
    bool free = true;
    vector <CEvent> ev;
    for (const auto &i: m){
        int dayMap = stoi(i.second.date.getDate().substr(0, 2));
        int monthMap = stoi(i.second.date.getDate().substr(3, 2));
        if (i.second.date.getDate() == s || (dayMap == day && month == monthMap && i.second.frequency == "Annual")){
            ev.push_back(i.second);
            free = false;
        }
    }

    if ( free ){
        cout << "\033[38;5;49;1m" << dayWeek << " " << s << " is free, you have nothing planned" << endl << endl;
    } else {
        cout << "\033[38;5;49;1m" << "Schedule on " << dayWeek << ", " << s << endl << endl;
        CInterface menu;
        for (auto &i: ev) {
            menu.eventShow(i);
            cout << endl;
        }
    }

}
