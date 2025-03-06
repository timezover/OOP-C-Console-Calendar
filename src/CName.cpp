#include "CName.h"
#include "CCommand.h"
#include <iostream>

void CName::inputAttr(const string & str){
    cout << "\033[38;5;14;1m~ Write the name of the event:" << endl;
    string s;
    while ( true ) {
        cout << "\t\033[38;5;14;1m>>\033[0m ";
        cout << "\033[38;5;231;1m";
        getline(cin, s);
        if (cin.eof()) {
            throw runtime_error("EOF reached while executing command");
        }
        removeSpace(s);
        if (s.empty()){
            cout << "\033[38;5;14;1m~ This field is necessary. Try again." << endl;
        } else {
            setAttr(s);
            break;
        }
    }
}

void CName::setAttr(const string &newAttr){
    name = newAttr;
}

string CName::getName() const{
    return name;
}

ostream & operator<<(ostream& os, const CName &obj){
    return os << obj.name;
}

bool CName::empty() const{
    return name.empty();
}