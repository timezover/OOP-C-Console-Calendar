/**
 * @author Yahor Byaliauski
 * @date 07.05.2023
 */

#pragma once
#include <map>
#include "CEvent.h"

/**
 * @brief Abstract parent-class represent calendar management
 */
class CCalendar{
public:
    virtual ~CCalendar() = default;

    /**
     * @brief Method prints matching calendar
     * @param[in] date String that represents month or year. Can be empty
     * @param[in] m Map of all available events
     */
    virtual void printCalendar(const string & date, const map <string, CEvent> & m) const;
};