#pragma once
#include "CAttribute.h"
#include <string>
#include <vector>

/**
 * @brief Class represents event's tags. Inherits CAttribute
 */
class CTag : public CAttribute{
private:
    vector <string> tag;
    string tag_check;
public:
    /**
     * @brief Fills tag_check with @param[in] t value
     * @param[in] t A Tag
     */
    CTag(const string & t);
    CTag() = default;

    /**
    * @brief Adds new tags
    * @param[in] newAttr Represents string that contains tags
    */
    void setAttr(const string & newAttr) override;

    /**
     * @return True if tag is valid, otherwise false
     * @note Tag is considered valid if it has '#' in the beginning
     */
    bool tagValid();

    /**
     * @brief Operator for tags' output
     * @param[out] os Out stream
     * @param[in] obj CTag object
     * @return Out stream
     */
    friend ostream& operator<<(ostream& os, const CTag &obj);

    /**
     * @return True if there are no tags, otherwise false
     */
    bool empty() const override;

    /**
      * @brief Calls interactive menu for tags' input
      * @param[in] str In case of CTag this string is empty
      * @note Tags are separated by space(s)
      */
    void inputAttr(const string & str) override;

    /**
     * @return Tag vector
     */
    vector <string> getTag() const;
};