#pragma once
#include <memory>
#include <string>
#include "CCommand.h"

using namespace std;

/**
 * @brief Removes spaces and tabulators in the beginning and in the end of the string
 * @param s reference on string
 */
void removeSpace(string & s);

/**
 * @brief Class represents application run and reading user's input
 */
class CApplication
{
private:
    bool live = true;
    string s;
    CCommand com;
public:
    CApplication();
    ~CApplication() = default;

    /**
     * @brief Method reads file with events
     */
    void readFile();

    /**
     * @brief Prints message at the start of the app
     */
    void helloMessage() const;

    /**
     * @brief Kills app
     */
    void appExit() const;

    /**
     * @brief Read user's input
     */
    void getLine();

    /**
     * @brief Method processes user's input
     */
    void commandExecute();

    /**
     * @return Bool value, that represents app life
     */
    bool getLive() const;
};
