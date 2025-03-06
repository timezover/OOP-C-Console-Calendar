#include "CPlace.h"
#include <iostream>
#include "CCommand.h"

void CPlace::inputAttr(const string & str){
    cout << "\033[38;5;14;1m~ Write the venue of the event (you can leave this field empty)" << endl;
    string newPlace;
    cout << "\t\033[38;5;14;1m>>\033[0m ";
    cout << "\033[38;5;231;1m";
    getline(cin, newPlace);
    if (cin.eof()) {
        throw runtime_error("EOF reached while executing command");
    }
    removeSpace(newPlace);
    setAttr(newPlace);
}

void CPlace::setAttr(const string &newAttr){
    place = newAttr;
}

string CPlace::getPlace() const{
    return place;
}

bool CPlace::empty() const{
    return place.empty();
}

ostream& operator<<(std::ostream& os, const CPlace &obj) {
    return os << obj.place;
}