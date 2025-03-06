#include "CParticipant.h"

void removeSpacePart(string & s){
    while(s.front() == ' ' || s.front() == '\t'){
        s = s.substr(1);
    }
    while(s.back() == ' ' || s.back() == '\t'){
        s.pop_back();
    }
}

void CParticipant::setAttr(const string & newAttr){
    stringstream ss(newAttr);
    string word;
    personName = {};
    while (getline(ss, word, ',')){
        removeSpacePart(word);
        personName.push_back(word);
    }
}

bool CParticipant::empty() const{
    return personName.empty();
}

void CParticipant::inputAttr(const string & str){
    cout << "\033[38;5;14;1m~ Add some participants to the event (you can leave this field empty)" << endl;
    string part;
    cout << "\t\033[38;5;14;1m>>\033[0m ";
    cout << "\033[38;5;231;1m";
    getline(cin, part);
    if (cin.eof()) {
        throw runtime_error("EOF reached while executing command");
    }
    setAttr(part);

}

ostream& operator<<(std::ostream& os, const CParticipant &obj){
    for (size_t i = 0; i < obj.personName.size(); i++){
        string s = ", ";
        if (i != 0){
            os << s;
        }
        os << obj.personName[i];
    }
    return os;
}