#include "CCommand.h"
#include "CInterface.h"
#include "CDate.h"
#include "CCalendarDay.h"
#include "CCalendarMonth.h"
#include "CCalendarYear.h"
#include "CSearch.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <memory>

void printCursor(){
    cout << "\033[38;5;99;1m>> \033[38;5;15;1m";
}

void removeSpace(string & s){
    while(s.front() == ' ' || s.front() == '\t'){
        s = s.substr(1);
    }
    while(s.back() == ' ' || s.back() == '\t'){
        s.pop_back();
    }
}

void CCommand::readCommand(const string & str){
    command = str;
}


CEvent CCommand ::readAttribute(const string & str) const{
    CEvent ev;

    string impId, impName, impDate, impTimeStart, impPlace, impFreq, impText, impTag, impAttend, impPart, impTimeEnd;

    impId = str.substr(0, 5);

    size_t startSub = str.find("[<name>]") + string("[<name>]").length();
    size_t endSub = str.find("[<date>]");
    impName = str.substr(startSub, endSub - startSub);

    startSub = str.find("[<date>]") + string("[<date>]").length();
    endSub = str.find("[<timestart>]");
    impDate = str.substr(startSub, endSub - startSub);

    startSub = str.find("[<timestart>]") + string("[<timestart>]").length();
    endSub = str.find("[<timeend>]");
    impTimeStart = str.substr(startSub, endSub - startSub);

    startSub = str.find("[<timeend>]") + string("[<timeend>]").length();
    endSub = str.find("[<place>]");
    impTimeEnd = str.substr(startSub, endSub - startSub);

    startSub = str.find("[<place>]") + string("[<place>]").length();
    endSub = str.find("[<tag>]");
    impPlace = str.substr(startSub, endSub - startSub);

    startSub = str.find("[<tag>]") + string("[<tag>]").length();
    endSub = str.find("[<text>]");
    impTag = str.substr(startSub, endSub - startSub);

    startSub = str.find("[<text>]") + string("[<text>]").length();
    endSub = str.find("[<frequency>]");
    impText = str.substr(startSub, endSub - startSub);

    startSub = str.find("[<frequency>]") + string("[<frequency>]").length();
    endSub = str.find("[<attendance>]");
    impFreq = str.substr(startSub, endSub - startSub);

    startSub = str.find("[<attendance>]") + string("[<attendance>]").length();
    endSub = str.find("[<participant>]");
    impAttend = str.substr(startSub, endSub - startSub);

    startSub = str.find("[<participant>]") + string("[<participant>]").length();
    impPart = str.substr(startSub);

    ev.name.setAttr(impName);
    ev.date.setAttr(impDate);
    ev.timeStart.setAttr(impTimeStart);
    ev.timeEnd.setAttr(impTimeEnd);
    ev.place.setAttr(impPlace);
    ev.text.setAttr(impText);
    ev.tag.setAttr(impTag);
    ev.participant.setAttr(impPart);
    ev.attendance = impAttend;
    ev.frequency = impFreq;
    ev.id = impId;

    return ev;
}

bool CCommand::mapFill(){
    ifstream event_file("build/events.txt");
    if (event_file.is_open()){
        string line;
        while (getline(event_file, line)){
            if (!line.empty() && line != "\n") {
                CEvent newEv;
                newEv = readAttribute(line);
                eventList.insert(make_pair(newEv.id, newEv));
            }
        }
    } else {
        return false;
    }
    return true;
}

void CCommand::exportEvents(const map <string, CEvent> &m) const{
    ofstream eventExp("build/eventexport.txt");
    if (eventExp.is_open()) {
        for (const auto &i: m){
            eventExp << "\tName: " << i.second.name << endl;
            if (i.second.frequency == "Annual"){
                eventExp << "Date: " << i.second.date.getDate().substr(0, 5) << " ";
            } else {
                eventExp << "Date: " << i.second.date << " ";
            }
            eventExp << i.second.frequency << endl;
            if (!i.second.timeStart.empty()){
                eventExp << "Time: " << i.second.timeStart << " - " << i.second.timeEnd << endl;
            }
            if (!i.second.place.empty()){
                eventExp << "Place: " << i.second.place << endl;
            }
            if (!i.second.tag.empty()){
                eventExp << "Tag: " << i.second.tag << endl;
            }
            if (!i.second.participant.empty()){
                eventExp << "Participants: " << i.second.participant << endl;
            }
            if (!i.second.text.empty()){
                eventExp << "Note: " << i.second.text;
            }
            eventExp << "\n\n";
        }
        cout << "\033[38;5;118;1mEvent export was successful" << endl;
    } else {
        cout << "\033[38;5;124;1mExport was not completed. Export file is damaged or does not exist" << endl;
    }
}

void CCommand :: execute(bool & r)
{
    if (command == "/exit"){
        r = false;
        return;
    }
    ifstream comm_file("build/commands.txt");
    int num;
    string str;
    if (comm_file.is_open()){
        string line;
        bool comExist = false;
        while (getline(comm_file, line)){
            size_t pos = line.find('-');
            str = line.substr(0, pos);
            num = stoi(line.substr(pos + 1));
            if (command == str) {
                comExist = true;
                break;
            }
        }
        if (!comExist){
            cout << "Command '" << command << "' does not exist. Type /help for showing all possible commands.\n";
            comm_file.close();
            return;
        }
        comm_file.close();
    } else {
        cout << "Error: command file does not exist" << endl;
        return;
    }

    if (num == 1){
        simpleOutput();
    } else if (num == 2){
        eventFind();
    } else if (num == 3){
        commandEvent();
    } else if (num == 4){
        commandCalendar();
    }
}

void CCommand::eventFind() const{
    CSearch evSearch(eventList);
    if (command == "/find event"){
        evSearch.eventSearch();
        cout << endl;
        CInterface menu;
        for (const auto &i: evSearch.getMap()){
            menu.eventShow(i.second);
            cout << endl;
        }
    }
    cout << "\033[38;5;220;1m~ Would you like to export these events?(yes/no)" << endl;
    cout << "\t>> \033[38;5;15;1m";
    string answer;
    getline(cin, answer);
    if (cin.eof()) {
        throw runtime_error("EOF reached while executing command");
    }
    removeSpace(answer);
    if (answer == "yes"){
        exportEvents(evSearch.getMap());
        cout << endl;
    } else if (answer == "no"){
        cout << "\033[38;5;220;1mEvents were not exported" << endl << endl;
    } else {
        cout << "\033[38;5;220;1mInvalid format" << endl << endl;
    }
}

void CCommand ::commandEvent(){
    if (command == "/set event"){
        CInterface menu;
        menu.eventSet(eventList);
        cout << endl;
    }

    if (command == "/get events"){
        CInterface menu;
        cout << endl;
        for (const auto &i: eventList){
            menu.eventShow(i.second);
            cout << endl;
        }
    }

    if (command == "/del event all"){
        cout << endl;
        cout << "\033[38;5;197;1m~ Are you sure you want to delete ALL events? [yes/no]" << endl;
        cout << "\t>>\033[38;5;15;1m ";
        string answer;
        getline(cin, answer);
        if (cin.eof()) {
            throw runtime_error("EOF reached while executing command");
        }
        removeSpace(answer);
        if (answer == "no"){
            cout << "\033[38;5;10;1mEvents were not deleted" << endl << endl;
        } else if (answer == "yes") {
            ofstream event_file("build/events.txt", ios::out | ios::trunc);
            eventList = {};
            event_file.close();
            cout << "\033[38;5;197;1mAll events were deleted" << endl << endl;
        } else {
            cout << "\033[38;5;197;1mInvalid command" << endl << endl;
        }
    }

    if (command == "/set id"){
        cout << "\033[38;5;14;1m~ Write id of the event in format NNNNN:" << endl;
        cout << "\t>>\033[0m ";
        cout << "\033[38;5;231;1m";
        string inId;
        getline(cin, inId);
        if (cin.eof()) {
            throw runtime_error("EOF reached while executing command");
        }
        removeSpace(inId);
        if (eventList.find(inId) == eventList.end()){
            cout << "\033[38;5;14;1m Id \033[38;5;105;1m" << inId << " \033[38;5;14;1mwas not found" << endl;
        } else {
            auto event = eventList.find(inId);
            CInterface menu;
            menu.idSet(event->second, eventList);
        }
    }

    if (command == "/del id"){
        cout << "\033[38;5;14;1m~ Write id of the event in format NNNNN:" << endl;
        cout << "\t>>\033[0m ";
        cout << "\033[38;5;231;1m";
        string inId;
        getline(cin, inId);
        if (cin.eof()) {
            throw runtime_error("EOF reached while executing command");
        }
        removeSpace(inId);
        if (eventList.find(inId) == eventList.end()){
            cout << "\033[38;5;14;1m Id \033[38;5;105;1m" << inId << " \033[38;5;14;1mwas not found" << endl;
        } else {
            auto event = eventList.find(inId);
            CInterface menu;
            if (menu.deleteEvent(event->second)){
                eventList.erase(event->second.id);
            }
        }
    }

}

void CCommand::commandCalendar() const{
    CInterface menu;
    int choice = menu.calendarChoice();
    unique_ptr <CCalendar> ptr;
    string str;
    if (choice == 1){
        ptr = make_unique<CCalendarDay>();
        str = "";
    } else if (choice == 2){
        str = menu.monthInput();
        ptr = make_unique<CCalendarMonth>();
    } else {
        str = menu.yearInput();
        ptr = make_unique<CCalendarYear>();
    }
    cout << endl;
    ptr->printCalendar(str, eventList);
    if (choice == 2 || choice == 3){
        cout << "\033[38;5;15;4mUnderscored\033[0m\033[38;5;15;1m days means that there is/are events" << endl << endl;
    }
}

void CCommand :: simpleOutput() const{
    if (command == "/help"){
        ifstream file("build/helpfile.txt");
        if (file.is_open()){
            string line;
            cout << "\033[38;5;15;1m";
            while (getline(file, line)){
                cout << line << endl;
            }
            file.close();
        } else {
            cout << "Error: helpfile does not exist" << endl;
        }
    }

    if (command == "/time"){
        cout << endl;
        chrono::system_clock::time_point currentTime = chrono::system_clock::now();
        time_t currentTime_t = chrono::system_clock::to_time_t(currentTime);

        char* timeOutput = ctime(&currentTime_t);
        string timeString(timeOutput);
        timeString = timeString.substr(11, 8);

        cout << "\033[38;5;177;1mCurrent time: " << timeString << endl << endl;

    }

    if (command == "/date"){
        cout << endl;

        chrono::system_clock::time_point now = chrono::system_clock::now();
        time_t current_time = chrono::system_clock::to_time_t(now);
        tm* current_date = localtime(&current_time);

        int year = current_date->tm_year + 1900;
        int month = current_date->tm_mon + 1;
        int day = current_date->tm_mday;
        string s = to_string(day);
        if (day < 10){
            s = "0" + s;
        }
        s += ".";
        if (month < 10){
            s = s + "0";
        }
        s += to_string(month);
        s += ".";
        s += to_string(year);
        string dayOfWeek = calculateDay(s);

        cout << "\033[38;5;177;1mDate: " << dayOfWeek << ", " << day << "/" << month << "/" << year << endl << endl;
    }

    if (command == "/clear"){
        for (int i = 0; i < 50; i++){
            cout << "\n";
        }
    }

}
