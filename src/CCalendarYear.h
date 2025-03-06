#pragma once
#include "CCalendar.h"
#include <map>

/**
 * @brief Class represents year calendar. Inherits CCalendar
 */
class CCalendarYear : public CCalendar{
public:
    CCalendarYear() = default;

    /**
     * @brief Method prints year calendar
     * @param[in] date String that represents year
     * @param[in] m Map of all available events
     * @note In this class method uses CCalendarMonth version of printCalendar to print every month calendar
     */
    void printCalendar(const string & date, const map <string, CEvent> &m) const override;
};
