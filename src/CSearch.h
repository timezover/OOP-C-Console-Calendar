#pragma once
#include "CEvent.h"
#include <map>
#include <vector>

/**
 * @brief Class represents event search management
 */
class CSearch{
private:
    map <string, CEvent> eventFindList;
public:

    /**
     * @param[in] m Map of all events
     * @note Constructor fills class' map with values of map of all events
     */
    CSearch(const map <string, CEvent> & m);
    ~CSearch() = default;

    /**
     * @brief Calls interactive menu for event search.
     * @note Attributes' fields can be left empty, if user doesn't want to search by these attributes
     * @note In attributes' fields user can write '|', which means that event can be found by two different certain attribute values at the same time
     */
    void eventSearch();

    /**
     * @return Map of found events
     */
    map <string, CEvent> getMap() const;

    /**
     * @brief Method finds among all events those, which fit search plan (attributes, than user had set)
     * @param[in] vName Vector of target attributes
     * @param[in] vDate Vector of target dates
     * @param[in] vPlace Vector of target Places
     * @param[in] vTag Vector of target Tags
     * @param[in] vFreq Vector of target frequencies
     * @note If vector is empty, search will be not completed by attributes of vector type
     */
    void foundEvents(const vector <string> &vName, const vector <string> &vDate, const vector <string> &vPlace,
                     const vector <string> &vTag, const string & vFreq);
};