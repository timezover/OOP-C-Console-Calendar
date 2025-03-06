#include "CSearch.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include "CDate.h"

string caseLower(const string & str){
    string lowerS = str;
    for (char &c: lowerS){
        c = tolower(c);
    }
    return lowerS;
}

CSearch::CSearch(const map<std::string, CEvent> &m){
    eventFindList = m;
}

map <string, CEvent> CSearch::getMap() const{
    return eventFindList;
}

void remTabSp(string & s){
    while(s.front() == ' ' || s.front() == '\t'){
        s = s.substr(1);
    }
    while(s.back() == ' ' || s.back() == '\t'){
        s.pop_back();
    }
}

bool checkTag(const vector <string> & v){
    for (const auto &i: v){
        if (i[0] != '#'){
            return false;
        }
    }
    return true;
}

bool checkDate(const vector <string> & v){
    for (const auto & i : v){
        if (!dateValid(i)){
            return false;
        }
    }
    return true;
}

void divideAtr(vector <string> & v, const string & s){
    stringstream ss(s);
    string atr;
    v = {};
    while (getline(ss, atr, '|')){
        remTabSp(atr);
        if (!atr.empty()) {
            v.push_back(atr);
        }
    }
}

void CSearch::foundEvents(const vector <string> &vName, const vector <string> &vDate,
                          const vector <string> &vPlace, const vector <string> &vTag, const string &vFreq){
    map <string, CEvent> findResult;
    for (auto &i: vName){
        for (auto &k: eventFindList){
            if (caseLower(i) == caseLower(k.second.name.getName())){
                findResult.insert(k);
            }
        }
    }

    if (!vName.empty()){
        eventFindList = findResult;
    }
    findResult = {};

    if (!vFreq.empty()){
        if (vFreq == "1"){
            for (auto &i: eventFindList){
                if (i.second.frequency == "One-time"){
                    findResult.insert(i);
                }
            }
        } else {
            for (auto &i: eventFindList){
                if (i.second.frequency == "Annual"){
                    findResult.insert(i);
                }
            }
        }
    }

    if (!vFreq.empty()){
        eventFindList = findResult;
    }
    findResult = {};

    for (auto &i: vDate){
        for (auto &k: eventFindList){
            if (k.second.date.getDate() == i || ((vFreq == "2" || vFreq.empty())
            && i.substr(0, 5) == k.second.date.getDate().substr(0, 5))){
                findResult.insert(k);
            }
        }
    }

    if (!vDate.empty()){
        eventFindList = findResult;
    }
    findResult = {};

    for (auto &i: vPlace){
        for (auto &k: eventFindList){
            if (caseLower(i) == caseLower(k.second.place.getPlace())){
                findResult.insert(k);
            }
        }
    }

    if (!vPlace.empty()){
        eventFindList = findResult;
    }
    findResult = {};

    for (auto &i: vTag){
        for (auto &k: eventFindList){
            for (auto &l: k.second.tag.getTag()){
                if (caseLower(i) == caseLower(l)){
                    findResult.insert(k);
                    break;
                }
            }
        }
    }

    if (!vTag.empty()){
        eventFindList = findResult;
    }
    findResult = {};
}

void CSearch::eventSearch(){
    vector <string> fName;
    vector <string> fDate;
    vector <string> fTag;
    vector <string> fPlace;
    string fFreq;
    string str;

    cout << "\033[38;5;220;1mInput following attributes. You can leave field empty if you don't want to search by this attribute" << endl;
    cout << "You can add more than one attribute in one field using '|'. It allows you to search by two attributes at the same time" << endl;
    cout << endl;
    cout << "Name: \033[38;5;15;1m";
    getline(cin, str);
    if (cin.eof()) {
        throw runtime_error("EOF reached while executing command");
    }
    remTabSp(str);
    divideAtr(fName, str);

    while ( true ) {
        cout << "\033[38;5;220;1mFrequency('1' - one-time, '2' - annual): \033[38;5;15;1m";
        getline(cin, str);
        if (cin.eof()) {
            throw runtime_error("EOF reached while executing command");
        }
        remTabSp(str);
        if ((str.length() != 1 || (str != "1" && str != "2")) && !str.empty()) {
            cout << "\033[38;5;220;1mInvalid format. ";
        } else {
            fFreq = str;
            break;
        }
    }

    while ( true ){
        cout << "\033[38;5;220;1mDate(DD.MM.YYYY): \033[38;5;15;1m";
        getline(cin, str);
        if (cin.eof()) {
            throw runtime_error("EOF reached while executing command");
        }
        remTabSp(str);
        divideAtr(fDate, str);
        if (!checkDate(fDate)){
            cout << "\033[38;5;220;1mInvalid format or year is not in range 2000-2100. ";
        } else {
            break;
        }
    }

    cout << "\033[38;5;220;1mPlace: \033[38;5;15;1m";
    getline(cin, str);
    if (cin.eof()) {
        throw runtime_error("EOF reached while executing command");
    }
    remTabSp(str);
    divideAtr(fPlace, str);

    while ( true ){
        cout << "\033[38;5;220;1mTag(#tag): \033[38;5;15;1m";
        getline(cin, str);
        if (cin.eof()) {
            throw runtime_error("EOF reached while executing command");
        }
        remTabSp(str);
        divideAtr(fTag, str);
        if (!checkTag(fTag)){
            cout << "\033[38;5;220;1mInvalid format. ";
        } else {
            break;
        }
    }

    foundEvents(fName, fDate, fPlace, fTag, fFreq);
    cout << endl;
    cout << "\t\t\033[38;5;220;1m Found events:" << endl;
}