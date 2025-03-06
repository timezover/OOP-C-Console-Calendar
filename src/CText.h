#pragma once
#include "CAttribute.h"

/**
 * @brief Class represents event note. Inherits CAttribute
 */
class CText : public CAttribute{
private:
    string note;
public:
    CText() = default;

    /**
    * @brief Sets new value for event's note
    * @param[in] newAttr Represents new note
    */
    void setAttr(const string & newAttr) override;

    /**
     * @return True if note is empty, otherwise false
     */
    bool empty() const override;

    /**
      * @brief Calls interactive menu for note input
      * @param[in] str Represents event's note
      * @note Place field can be left empty
      */
    void inputAttr(const string & str) override;

    /**
     * @brief Operator for note output
     * @param[out] os Out stream
     * @param[in] obj CText object
     * @return Out stream
     */
    friend ostream& operator<<(ostream& os, const CText &obj);
};