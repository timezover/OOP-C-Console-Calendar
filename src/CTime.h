#pragma once
#include <chrono>
#include "CAttribute.h"
using namespace std;

/**
 * @brief Splits time, represented in string, into 2 int values
 * @param[in] time Time, represented in string and in format hh:mm
 * @param[out] hours Hours
 * @param[out] min Minutes
 */
void splitTime(const string & time, int & hours, int & min);

/**
 * @brief Checks if times are set correctly
 * @param[in] startTime Time when events starts
 * @param[in] endTime Time when events end
 * @return True if times are set correctly, otherwise false
 * @note Time set is considered as correct when start time is earlier than end time
 */
bool checkOrder(const string & startTime, const string & endTime);

/**
 * @brief Class represents start time or end time of the events. Inherits CAttribute
 */
class CTime : public CAttribute{
private:
    string time;
public:

    /**
     * @brief Fills time value with @param[in] t
     * @param[in] t Time
     */
    CTime(const string & t);
    CTime() = default;

    /**
    * @brief Sets new value for event's time
    * @param[in] newAttr Represents new time
    */
    void setAttr(const string & newAttr) override;

    /**
      * @brief Calls interactive menu for time input
      * @param[in] str In case of CTime this string is empty
      * @note Time field can bel eft empty. But if user set start time, than he must set end time too
      */
    void inputAttr(const string & str) override;

    /**
     * @brief Operator for time output
     * @param[out] os Out stream
     * @param[in] obj CTime object
     * @return Out stream
     */
    friend ostream& operator<<(ostream& os, const CTime &obj);

    /**
     * @return True if time is empty, otherwise false
     */
    bool empty() const override;

    /**
     * @brief Checks if time is valid
     * @return True if time is valid, otherwise false
     * @note Time is considered as valid if it is in format hh.mm and hours are in range 0-23 and minutes are in range 0-59
     */
    bool timeValid();

    /**
     * @return Time value
     */
    string getTime() const;
};
