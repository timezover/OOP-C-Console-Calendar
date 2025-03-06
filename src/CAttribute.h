#pragma once
#include <string>
#include <iostream>
using namespace std;

/**
 * @brief Abstract parent-class that represents event's attribute
 */
class CAttribute{
public:
    virtual ~CAttribute() = default;

    /**
     * @brief Method sets attribute's value
     * @param[in] newAttr Value of attribute
     */
    virtual void setAttr(const string & newAttr);

    /**
     * @brief Method calls matching menu for each attribute
     * @param[in] str Supplementary string for some attributes, can be empty
     */
    virtual void inputAttr(const string & str);

    /**
     * @return true if attribute's empty, otherwise false
     */
    virtual bool empty() const;
};