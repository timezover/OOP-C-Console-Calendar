#include "CInterface.h"
#include "CEvent.h"
#include <iostream>
#include <fstream>

string createId(){
    string id;
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < 5; i++){
        int randNum = rand() % 10;
        char randChar = randNum + '0';
        id += randChar;
    }
    return id;
}

bool checkId(const string & id){
    ifstream file("build/events.txt");
    if (file.is_open()){
        string line;
        while (getline(file, line)){
            line = line.substr(0, 5);
            if (line == id){
                return false;
            }
        }
        file.close();
    } else {
        cout << "Error: event file does not exist" << endl;
    }
    return true;
}

string CInterface::monthInput() const{
    cout << "\033[38;5;49;1m~ Write month in format MM.YYYY" << endl;
    string d;
    while ( true ) {
        cout << "\t>> \033[38;5;15;1m";
        getline(cin, d);
        if (cin.eof()) {
            throw runtime_error("EOF reached while executing command");
        }
        removeSpace(d);
        d = "01." + d;
        if (dateValid(d)){
            break;
        } else {
            cout << "\033[38;5;49;1m~ Invalid format or year is not in range 2000-2100. Write month in format MM.YYYY" << endl;
        }
    }
    return d;
}

string CInterface::yearInput() const{
    cout << "\033[38;5;49;1m~ Write year in format YYYY" << endl;
    string d;
    while ( true ){
        cout << "\t>> \033[38;5;15;1m";
        getline(cin, d);
        if (cin.eof()) {
            throw runtime_error("EOF reached while executing command");
        }
        removeSpace(d);
        d = "01.01." + d;
        if (dateValid(d)){
            break;
        } else {
            cout << "\033[38;5;49;1m~ Invalid format or year is not in range 2000-2100. Write year in format YYYY" << endl;
        }
    }
    return d;
}

int CInterface ::calendarChoice() const{
    cout << "\033[38;5;49;1m~ Write '1' if you want to print day calendar, '2' for month and '3' for year" << endl;
    string str;
    while ( true ){
        cout << "\t>> \033[38;5;15;1m";
        getline(cin, str);
        if (cin.eof()) {
            throw runtime_error("EOF reached while executing command");
        }
        removeSpace(str);
        if (str.length() != 1){
            cout << "\033[38;5;49;1m~ Invalid format. Write '1' if you want to print day calendar, '2' for month and '3' for year" << endl;
        } else if (str[0] == '1'){
            return 1;
        } else if (str[0] == '2'){
            return 2;
        } else if (str[0] == '3'){
            return 3;
        } else {
            cout << "\033[38;5;49;1mInvalid format. Write '1' if you want to print day calendar, '2' for month and '3' for year" << endl;
        }
    }
}

bool CInterface::deleteEvent(CEvent & ev) const{
    eventShow(ev);
    cout << "\033[38;5;124;1m~ Are you sure you want to delete this event?(yes/no)" << endl;
    cout << "\t>> \033[38;5;15;1m";
    string answer;
    getline(cin, answer);
    if (cin.eof()) {
        throw runtime_error("EOF reached while executing command");
    }
    removeSpace(answer);
    if (answer == "yes"){
        ev.eventFileDelete();
        cout << "\033[38;5;106;1mEvent was deleted" << endl << endl;
        return true;
    } else if (answer == "no"){
        cout << "\033[38;5;124;1mEvent was not deleted" << endl << endl;
    } else{
        cout << "\033[38;5;124;1mInvalid format" << endl << endl;
    }
    return false;
}

void CInterface ::eventSet(map <string, CEvent> & m) const{
    string id;
    CEvent event;

    while ( true ){
        id = createId();
        if (checkId(id)){
            break;
        }
    }
    event.id = id;
    event.attrChange("", &event.name);
    cout << endl;
    event.freqSet();
    cout << endl;
    event.attrChange(event.frequency, &event.date);
    cout << endl;
    event.validTimeSet(m);
    cout << endl;
    event.attrChange("", &event.place);
    cout << endl;
    event.attrChange("", &event.tag);
    cout << endl;
    event.attrChange("", &event.text);
    cout << endl;

    event.fileImport();
    m.insert(make_pair(event.id, event));

    cout << "\033[38;5;14;1mEvent was successfully added! ^_^  Event id is \033[38;5;135;1m" << event.id << endl;
}

void CInterface::idSet(CEvent &ev, const map <string, CEvent> &m){
    cout << endl;
    eventShow(ev);
    cout << endl;
    cout << "\033[38;5;14;1m~ Which attribute you would like to change? Type certain number to change:" << endl;
    cout << "1 - name, 2 - date, 3 - time, 4 - place, 5 - frequency" << endl;
    cout << "6 - attendance, 7 - note, 8 - add participant, 9 - add tag" << endl;
    cout << "\t>> \033[38;5;15;1m";
    string answer;
    getline(cin, answer);
    if (cin.eof()) {
        throw runtime_error("EOF reached while executing command");
    }
    removeSpace(answer);
    if (answer != "1" && answer != "2" && answer != "3" && answer != "4" &&
        answer != "5" && answer != "6" && answer != "7" && answer != "8" && answer != "9"){
        cout << "\033[38;5;14;1m~ Invalid format" << endl;
        return;
    }

    if (answer == "1"){
        ev.attrChange("", &ev.name);
        cout << endl;
    }

    if (answer == "2"){
        ev.attrChange(ev.frequency, &ev.date);
        cout << endl;
    }

    if (answer == "3"){
        ev.validTimeSet(m);
        cout << endl;
    }

    if (answer == "4"){
        ev.attrChange("", &ev.place);
        cout << endl;
    }

    if (answer == "5"){
        string prevFreq = ev.frequency;
        ev.freqSet();
        cout << endl;
        if (prevFreq == "Annual" && ev.frequency == "One-time"){
            ev.attrChange(ev.frequency, &ev.date);
            cout << endl;
        }
    }

    if (answer == "6"){
        ev.atSet();
        cout << endl;
    }

    if (answer == "7"){
        ev.attrChange("", &ev.text);
        cout << endl;
    }

    if (answer == "8"){
        ev.attrChange("", &ev.participant);
        cout << endl;
    }

    if (answer == "9"){
        ev.attrChange("", &ev.tag);
        cout << endl;
    }

    ev.eventFileChange();
    cout << "\033[38;5;14;1m~ Attribute was successfully changed ^_^" << endl;
    cout << endl;
}

void CInterface ::eventShow(const CEvent & ev) const{
    cout << "\t\t\033[38;5;82;1m" << ev.name << endl;
    cout << "\t\033[38;5;57;1mAttendance: \033[38;5;15;1m" << ev.attendance << endl;
    cout << "\t\033[38;5;57;1mDate: \033[38;5;15;1m" << ev.frequency << " ";
    if (ev.frequency == "Annual"){
        cout << ev.date.getDate().substr(0, 5);
    } else {
        cout << calculateDay(ev.date.getDate()) << ", " << ev.date;
    }
    cout << endl;
    if (!ev.timeStart.empty()){
        cout << "\t\033[38;5;57;1mTime: \033[38;5;15;1m";
        cout << ev.timeStart.getTime() << " - " << ev.timeEnd << endl;
    }
    if (!ev.place.empty()) {
        cout << "\t\033[38;5;57;1mPlace: \033[38;5;15;1m" << ev.place << endl;
    }
    if (!ev.tag.empty()){
        cout << "\t\033[38;5;57;1mTag: \033[38;5;15;1m" << ev.tag << endl;
    }
    if (!ev.text.empty()) {
        cout << "\t\033[38;5;57;1mText: \033[38;5;15;1m" << ev.text << endl;
    }
    if (!ev.participant.empty()){
        cout << "\t\033[38;5;57;1mParticipants: \033[38;5;15;1m" << ev.participant << endl;
    }
    cout << "\t\033[38;5;57;1mID: \033[38;5;105;1m" << ev.id << endl;
}