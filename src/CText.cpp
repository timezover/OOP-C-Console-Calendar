#include "CText.h"
#include "CCommand.h"

void CText::inputAttr(const string & str){
    string text_;
    cout << "\033[38;5;14;1m~ Write a note to the event (you can leave this field empty)" << endl;
    cout << "\t\033[38;5;14;1m>>\033[0m ";
    cout << "\033[38;5;231;1m";
    getline(cin, text_);
    if (cin.eof()) {
        throw runtime_error("EOF reached while executing command");
    }
    removeSpace(text_);
    setAttr(text_);
}

void CText::setAttr(const string &newAttr){
    note = newAttr;
}

std::ostream& operator<<(std::ostream& os, const CText &obj){
    return os << obj.note;
}

bool CText::empty() const{
    return note.empty();
}