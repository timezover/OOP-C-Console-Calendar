#include "CCalendarYear.h"
#include "CCalendarMonth.h"
#include <iostream>

void CCalendarYear::printCalendar(const string &date, const map<string, CEvent> & m) const{
    string year = date.substr(6);
    for (int i = 1; i <= 12; i++){
        CCalendarMonth ccm;
        string dateRes;
        string month = to_string(i);
        if (i < 10) {
            month = "0" + month;
        }
        dateRes = "01." + month;
        dateRes += ".";
        dateRes += year;
        ccm.printCalendar(dateRes, m);
    }
}
