#include "CTag.h"
#include "CCommand.h"
#include <string>
#include <sstream>

CTag::CTag(const string & t){
    tag_check = t;
}

bool CTag::tagValid(){
    istringstream iss(tag_check);
    string word;

    while (iss >> word) {
        if (word.empty() || word[0] != '#') {
            return false;
        }
    }

    return true;
}

vector <string> CTag::getTag() const{
    return tag;
}

void CTag::setAttr(const std::string &newAttr){
    istringstream iss(newAttr);
    string word;
    tag = {};

    while (iss >> word){
        tag.push_back(word);
    }
}

void CTag::inputAttr(const string & str){
    cout << "\033[38;5;14;1m~ Add some tag to the event in format #tag (you can leave this field empty)" << endl;
    string tag_;
    while ( true ){
        cout << "\t\033[38;5;14;1m>>\033[0m ";
        cout << "\033[38;5;231;1m";
        getline(cin, tag_);
        if (cin.eof()) {
            throw runtime_error("EOF reached while executing command");
        }
        removeSpace(tag_);
        CTag t(tag_);
        if (t.tagValid() || tag_.empty()){
            setAttr(tag_);
            break;
        } else {
            cout << "\033[38;5;14;1m~ Invalid tag format. Add some tag to the event in format #tag" << endl;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const CTag &obj) {
    for (size_t i = 0; i < obj.tag.size(); i++){
        string s = " ";
        if (i != 0){
            os << s;
        }
        os << obj.tag[i];
    }
    return os;
}

bool CTag::empty() const{
    return tag.empty();
}