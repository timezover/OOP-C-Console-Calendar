#pragma once
#include "CCommand.h"
#include "CEvent.h"
#include "CCalendarMonth.h"
#include "CCalendarYear.h"
#include "CCalendarDay.h"
#include <map>

/**
 * @brief Class represents interactive menu management
 */
class CInterface {
public:
    CInterface() = default;
    ~CInterface() = default;

    /**
     * @brief Calls interactive menu for event set. Inserts an event in event map and in events.txt file
     * @param[out] m Map of all events
     */
    void eventSet(map <string, CEvent> & m) const;

    /**
     * @brief Prints an event (attributes)
     * @note Attributes, thar are empty, won't be printed
     * @param[in] ev An event
     */
    void eventShow(const CEvent & ev) const;

    /**
     * @brief Calls interactive menu for event's attribute change
     * @note Event is found by it's id
     * @param[out] ev An event
     * @param[in] m Map of all events
     */
    void idSet(CEvent & ev, const map <string, CEvent> &m);

    /**
     * @brief Calls interactive menu for event discard
     * @note Event is found by its id. Event will also be erased from events.txt file
     * @param[out] ev An event
     * @return True if event with following id exists, otherwise false
     */
    bool deleteEvent(CEvent & ev) const;

    /**
     * @brief Calls interactive menu for calendar select (day, month or year)
     * @return True if choice is valid, otherwise false
     */
    int calendarChoice() const;

    /**
     * @brief Calls interactive menu for month calendar date input
     * @return Date for calendar
     */
    string monthInput() const;

    /**
     * @brief Calls interactive menu for year input
     * @return Date for calendar
     */
    string yearInput() const;
};