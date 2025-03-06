#pragma once
#include "CText.h"
#include "CTime.h"
#include "CPlace.h"
#include "CDate.h"
#include "CName.h"
#include "CTag.h"
#include "CParticipant.h"
#include <map>

/**
 * @brief Class represents event with it's attributes
 */
class CEvent{
private:
    CText text;
    CTime timeStart;
    CTime timeEnd;
    CPlace place;
    CDate date;
    CName name;
    CTag tag;
    CParticipant participant;

    /**
     * @brief Event's id is unique
     */
    string id;
    string attendance;
    string frequency;
public:

    /**
     * @note Constructor of CEvent sets attendance value on "Mandatory" by default
     */
    CEvent();
    ~CEvent() = default;

    /**
     * @brief Method imports an event to file events.txt
     * @note Imported event is represented in string, where attributes are divided by matching delimiters
     * @return True if file had open successfully, otherwise false
     */
    bool fileImport() const;

    /**
     * @brief Changes event's information in events.txt file
     * @note Method rewrites events.txt file without changed event and than adds already changed event
     * @return True if file had open successfully, otherwise false
     */
    bool eventFileChange() const;

    /**
     * @brief Deletes event from events.txt file
     * @note Method rewrites event.s txt file without following event
     */
    void eventFileDelete() const;

    /**
     * @param[in] at Represents user's answer
     * @return True if answer is valid, false otherwise
     * @note Answer is considered valid if it's "1" or "2"
     */
    bool choiceValid(const string & at);

    /**
     * @brief Calls interactive menu for frequency input
     */
    void freqSet();

    /**
     * @brief Calls interactive menu for attendance input
     */
    void atSet();

    /**
     * @brief Calls interactive menu for time set
     * @note Method checks collision of events in one day. If collision is found, app gives user a choice, leave it or change event's time
     * @note Method checks time order, if end time of the event is earlier than start time, time set will restart
     * @param[in] m Map of all events
     */
    void validTimeSet(const map <string, CEvent> & m);

    /**
     * @brief Checks collision with another events
     * @param[in] m Map of all events
     * @return Vector of events that collide with set event
     */
    vector <CEvent> checkCollision(const map <string, CEvent> & m);

    /**
     * @brief Changes attribute's value
     * @param[in] str Attribute value
     * @param[in] attr Pointer on event's attribute that has to be changed
     */
    void attrChange(const string & str, CAttribute * attr);

    friend class CInterface;
    friend class CCommand;
    friend class CCalendarDay;
    friend class CCalendarMonth;
    friend class CSearch;
};