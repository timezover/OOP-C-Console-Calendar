#pragma once
#include "CAttribute.h"
#include <string>

/**
 * @brief Class represents name of the event. Inherits CAttribute
 */
class CName : public CAttribute{
private:
    string name;
public:
    CName () = default;

    /**
    * @brief Sets new value for name
    * @param[in] newAttr Represents new name
    */
    void setAttr(const string & newAttr) override;

    /**
      * @brief Calls interactive menu for name input
      * @param[in] str Represents event name
      * @note Name is necessary attribute for every event
      */
    void inputAttr(const string & str) override;

    /**
     * @brief Operator for name output
     * @param[out] os Out stream
     * @param[in] obj CName object
     * @return Out stream
     */
    friend ostream& operator<<(ostream& os, const CName &obj);

    /**
     * @return True if name is empty, otherwise false
     */
    bool empty() const override;

    /**
     * @return Name value
     */
    string getName() const;
};