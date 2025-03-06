#pragma once
#include "CAttribute.h"
#include <string>

/**
 * @brief Class represents event's place. Inherits CAttribute
 */
class CPlace : public CAttribute{
private:
    string place;
public:
    CPlace () = default;

    /**
    * @brief Sets new value for event's place
    * @param[in] newAttr Represents new place
    */
    void setAttr(const string & newAttr) override;

    /**
      * @brief Calls interactive menu for place input
      * @param[in] str Represents event's place
      * @note Place field can be left empty
      */
    void inputAttr(const string & str) override;

    /**
     * @brief Operator for place output
     * @param[out] os Out stream
     * @param[in] obj CPlace object
     * @return Out stream
     */
    friend ostream& operator<<(std::ostream& os, const CPlace &obj);

    /**
     * @return True if place is empty, otherwise false
     */
    bool empty() const override;

    /**
     * @return Place value
     */
    string getPlace() const;
};