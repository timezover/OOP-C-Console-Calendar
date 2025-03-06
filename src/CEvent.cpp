#include "CEvent.h"
#include "CInterface.h"
#include <fstream>
#include <iostream>

bool ifCollides(const std::string& timeStart1, const std::string& timeEnd1, const std::string& timeStart2, const std::string& timeEnd2) {
    int hoursStart1, hoursStart2;
    int minutesStart1, minutesStart2;
    int hoursEnd1, hoursEnd2;
    int minutesEnd1, minutesEnd2;

    splitTime(timeStart1, hoursStart1, minutesStart1);
    splitTime(timeEnd1, hoursEnd1, minutesEnd1);
    splitTime(timeStart2, hoursStart2, minutesStart2);
    splitTime(timeEnd2, hoursEnd2, minutesEnd2);

    int totalMinStart1 = hoursStart1 * 60 + minutesStart1;
    int totalMinEnd1 = hoursEnd1 * 60 + minutesEnd1;
    int totalMinStart2 = hoursStart2 * 60 + minutesStart2;
    int totalMinEnd2 = hoursEnd2 * 60 + minutesEnd2;

    if (totalMinStart1 >= totalMinStart2 && totalMinStart1 <= totalMinEnd2) {
        return true;
    }
    if (totalMinEnd1 >= totalMinStart2 && totalMinEnd1 <= totalMinEnd2) {
        return true;
    }
    if (totalMinStart2 >= totalMinStart1 && totalMinStart2 <= totalMinEnd1) {
        return true;
    }
    if (totalMinEnd2 >= totalMinStart1 && totalMinEnd2 <= totalMinEnd1) {
        return true;
    }

    return false;
}

CEvent::CEvent(){
    attendance = "Mandatory";
}

void CEvent::eventFileDelete() const{
    ifstream eventFileIn("build/events.txt");
    if (eventFileIn.is_open()) {
        vector<string> lines;
        string line;
        while (getline(eventFileIn, line)) {
            if (line.substr(0, 5) != id) {
                lines.push_back(line);
            }
        }
        eventFileIn.close();

        ofstream eventFileOut("build/events.txt");
        for (const auto &i: lines){
            eventFileOut << i << endl;
        }
    }
}

bool CEvent::fileImport() const{
    ofstream event_file("build/events.txt", ios::app);
    if (event_file.is_open()){
        event_file << endl;
        event_file << id << ":";
        event_file << "[<name>]" << name;
        event_file << "[<date>]" << date;
        event_file << "[<timestart>]" << timeStart;
        event_file << "[<timeend>]" << timeEnd;
        event_file << "[<place>]" << place;
        event_file << "[<tag>]" << tag;
        event_file << "[<text>]" << text;
        event_file << "[<frequency>]" << frequency;
        event_file << "[<attendance>]" << attendance;
        event_file << "[<participant>]" << participant;
    } else {
        return false;
    }
    return true;
}

bool CEvent::eventFileChange() const{
    ifstream eventFileIn("build/events.txt");
    if (eventFileIn.is_open()) {
        vector<string> lines;
        string line;
        while (getline(eventFileIn, line)) {
            if (line.substr(0, 5) != id) {
                lines.push_back(line);
            }
        }
        eventFileIn.close();

        ofstream eventFileOut("build/events.txt");
        for (const auto &i: lines){
            eventFileOut << i << endl;
        }
        fileImport();
    } else {
        return false;
    }
    return true;
}

bool CEvent::choiceValid(const string &at){
    if (at.length() != 1){
        return false;
    }
    if (at.front() != '1' && at.front() != '2'){
        return false;
    }

    if (at == "1"){
        frequency = "One-time";
    } else {
        frequency = "Annual";
    }
    return true;
}

vector <CEvent> CEvent::checkCollision(const map <string, CEvent> & m){
    vector <CEvent> possibleCol;
    for (const auto &i: m){
        if ((i.second.date.getDate() == date.getDate() && id != i.second.id)
            || (i.second.frequency == "Annual" && i.second.id != id && i.second.date.getDate().substr(0, 5) == date.getDate().substr(0, 5))){
            possibleCol.push_back(i.second);
        }
    }
    vector <CEvent> collisions;
    for (const auto &i: possibleCol){
        if (ifCollides(timeStart.getTime(), timeEnd.getTime(), i.timeStart.getTime(), i.timeEnd.getTime())){
            collisions.push_back(i);
        }
    }
    return collisions;
}

void CEvent::validTimeSet(const map <string, CEvent> & m) {
    while (true) {
        bool validTime = true;
        vector<CEvent> col;
        cout << "\033[38;5;14;1m~ Write start time of the event in format HH:MM (you can leave this field empty)" << endl;
        attrChange("start", &timeStart);
        if (!timeStart.empty()) {
            cout << "\033[38;5;14;1m~ Write end time of the event in format HH:MM" << endl;
            attrChange("end", &timeEnd);
            if (timeEnd.empty()) {
                cout << "\033[38;5;14;1m~ Invalid format." << endl;
                validTime = false;
            } else if (!checkOrder(timeStart.getTime(), timeEnd.getTime())) {
                cout << "\033[38;5;14;1m~ Invalid format: End-time is earlier than start-time." << endl;
                validTime = false;
            }
            if (validTime) {
                col = checkCollision(m);
                if (!col.empty()) {
                    cout << "\033[38;5;14;1m~ New event collides with following events:" << endl;
                    for (const auto &i: col) {
                        CInterface menu;
                        menu.eventShow(i);
                        cout << endl;
                    }
                    cout << "\033[38;5;14;1m~ Do you wish to ignore collision ('1') or change time of the event ('2') ?" << endl;
                    string answer;
                    while (true) {
                        cout << "\t>> ";
                        cout << "\033[38;5;15;1m";
                        getline(cin, answer);
                        if (cin.eof()) {
                            throw runtime_error("EOF reached while executing command");
                        }
                        removeSpace(answer);
                        if (answer == "1" || answer == "2") {
                            break;
                        } else {
                            cout << "\033[38;5;14;1m~ Invalid format. Ignore collision - '1', change time - '2'"
                                 << endl;
                        }
                    }
                    if (answer == "1") {
                        break;
                    }
                } else {
                    break;
                }
            }
        } else {
            break;
        }
    }
}

void CEvent::freqSet(){
    cout << "\033[38;5;14;1m~ Choose between one-time event ( type '1' ) or annual ( type '2' ):" << endl;
    while ( true ){
        string attend;
        cout << "\t\033[38;5;14;1m>>\033[0m ";
        cout << "\033[38;5;231;1m";
        getline(cin, attend);
        if (cin.eof()) {
            throw runtime_error("EOF reached while executing command");
        }
        removeSpace(attend);
        if (choiceValid(attend)){
            break;
        } else {
            cout << "\033[38;5;14;1m~ Wrong format. Try again" << endl;
        }
    }
}

void CEvent::atSet(){
    cout << "\033[38;5;14;1m~ Choose between mandatory event ( type '1' ) or optional ( type '2' ):" << endl;
    while ( true ){
        string answer;
        cout << "\t\033[38;5;14;1m>> ";
        cout << "\033[38;5;15;1m";
        getline (cin, answer);
        if (cin.eof()) {
            throw runtime_error("EOF reached while executing command");
        }
        removeSpace(answer);
        if (answer == "1"){
            attendance = "Mandatory";
            break;
        } else if (answer == "2"){
            attendance = "Optional";
            break;
        } else {
            cout << "\033[38;5;14;1m~ Wrong format. Try again" << endl;
        }
    }
}

void CEvent::attrChange(const string & str, CAttribute *attr){
    attr->inputAttr(str);
}