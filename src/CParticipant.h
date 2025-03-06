#pragma once
#include "CAttribute.h"
#include <vector>
#include <sstream>

/**
 * @brief Class represents event participants. Inherits CAttribute
 */

class CParticipant : public CAttribute{
private:
    vector <string> personName;
public:
    CParticipant () = default;

    /**
    * @brief Adds new participants
    * @param[in] newAttr Represents string that contains participants
    */
    void setAttr(const string & newAttr) override;

    /**
      * @brief Calls interactive menu for participants' input
      * @param[in] str In case of CParticipant this string is empty
      * @note Participants must be separated by commas (written in menu)
      */
    void inputAttr(const string & str) override;

    /**
     * @return True if there are no participants, otherwise false
     */
    bool empty() const override;

    /**
     * @brief Operator for participants' output
     * @param[out] os Out stream
     * @param[in] obj CParticipant object
     * @return Out stream
     */
    friend std::ostream& operator<<(std::ostream& os, const CParticipant &obj);
};
