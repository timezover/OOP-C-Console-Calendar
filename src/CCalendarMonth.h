#pragma once
#include "CCalendar.h"
#include <vector>
#include <map>

/**
 * @brief Class represents month calendar. Inherits CCalendar
 */
class CCalendarMonth: public CCalendar{
private:
    vector <string> months {"January", "February", "March",
                            "April", "May", "June",
                            "July", "August", "September",
                            "October", "November", "December"};
    map <string, int> weekDays {{"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3}, {"Thursday", 4},
                                {"Friday", 5}, {"Saturday", 6}, {"Sunday", 7}};
public:
    CCalendarMonth() = default;

    /**
     * @brief Method prints any month calendar
     * @param[in] date String that represents month
     * @param[in] m Map of all available events
     */
    void printCalendar (const string & date, const map <string, CEvent> & m) const override;
};
