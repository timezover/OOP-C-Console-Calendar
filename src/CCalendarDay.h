#pragma once
#include "CCalendar.h"
#include "CEvent.h"

/**
 * @brief Class represents day calendar. Inherits CCalendar
 */
class CCalendarDay : public CCalendar{
public:
    CCalendarDay() = default;

    /**
     * @brief Method prints all events on certain day.
     * @param date In case of day calendar, this string is empty
     * @param m Map of all available events
     */
    void printCalendar (const string & date, const map <string, CEvent> & m) const override;
};