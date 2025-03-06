#pragma once
#include <string>
#include "CEvent.h"
#include <map>
using namespace std;

/**
 * @brief Removes spaces and tabulators in the beginning and in the end of the string
 * @param[out] s Reference on string
 */
void removeSpace(string & s);

/**
 * @brief Prints light blue cursor
 */
void printCursor();

/**
 * @brief Class represents command management and different interactive menu
 */
class CCommand {
private:
    string command;
public:
    CCommand() = default;
    ~CCommand() = default;

    /**
     * @brief Map of all events, where key is event's id and value is event itself
     */
    map<string, CEvent> eventList;

    /**
     * @brief Method execute command
     * @param[out] r Reference on bool value, that represents app life
     */
    void execute(bool &r);

    /**
     * @brief Checks if command is valid.
     * @param[in] str User's input
     */
    void readCommand(const string &str);

    /**
     * @note Method processes a line that represents an event. Line consists of attributes, that are divided by delimiters matching every attribute
     * @param[in] str String that represents information about event
     * @return Event represented in CEvent object
     */
    CEvent readAttribute(const string &str) const;

    /**
     * @brief Method reads information from event file and fills map
     * @return True if file had opened successfully, false otherwise
     */
    bool mapFill();

    /**
     * @note Method represents type of commands that print some useful simple information for user
     */
    void simpleOutput() const;

    /**
     * @note Method represents type of commands that manage events
     */
    void commandEvent();

    /**
     * @note Method represents type of commands that manage calendars
     */
    void commandCalendar() const;

    /**
     * @note Method represents type of commands that manage event search
     */
    void eventFind() const;

    /**
     * @brief Exports events in eventexport.txt file
     * @param[in] m Map that holds events, searched by user by attributes
     */
    void exportEvents(const map <string, CEvent> &m) const;
};