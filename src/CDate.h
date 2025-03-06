#pragma once
#include <string>
#include "CAttribute.h"
using namespace std;

/**
 * @brief Calculated day of the week based on date
 * @param[in] s Date represented in string
 * @return Day of the week
 * @warning Due to limitations of library <chrono>, application accepts dates betwen 2000 and 2100 years
 */
string calculateDay(const string & s);

/**
 * @brief Checks if date is valid
 * @param[in] date Date represented in string
 * @return True if date is valid, false otherwise
 * @note Date is considered as valid if it is in format dd.mm.yyyy and in year is less than 2100 and more than 2000
 */
bool dateValid(const string & date);

/**
 * @brief Class represents date of the event. Inherits CAttribute
 */
class CDate: public CAttribute{
private:
    string date;
public:
    CDate () = default;

    /**
     * @brief Sets new value for date
     * @param[in] newAttr Represents new date
     */
    void setAttr(const string & newAttr) override;

    /**
     * @brief Calls interactive menu for date input
     * @param[in] str Represents frequency of the event
     * @note If the event's frequency is one-time, date must be filled in format dd.mm, otherwise in format dd.mm.yyyy
     */
    void inputAttr(const string & str) override;

    /**
     * @brief Operator for date output
     * @param[out] os Out stream
     * @param[in] obj CDate object
     * @return Out stream
     */
    friend ostream& operator <<(ostream& os, const CDate &obj);

    /**
     * @return True if date is empty, false otherwise
     */
    bool empty() const override;

    /**
     * @return Date value
     */
    string getDate() const;
};