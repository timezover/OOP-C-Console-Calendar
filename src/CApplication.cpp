#include "CApplication.h"
#include "CCommand.h"
#include <unistd.h>
#include <iostream>
#include <string>

CApplication::CApplication(){
    helloMessage();
}

void CApplication ::appExit() const{
    for (int i = 0; i < 50; i++){
            cout << "\n";
    }
    cout << "\033[38;5;196;1m";
    cout << "\033[?25l";
    cout << "Exiting";
    cout.flush();
    for (int i = 0; i < 3; i++){
        usleep(250000);
        cout << ".";
        cout.flush();
    }
    usleep(250000);
    cout << endl << endl << "\033[?25h";
    cout << "\033[0m";
    cout.flush();
}

void CApplication :: getLine(){
    printCursor();
    getline(cin, s);
    if (cin.eof()) {
        throw std::runtime_error("EOF reached while executing command");
    }
    removeSpace(s);
}

void CApplication :: commandExecute(){
    com.readCommand(s);
    if (!s.empty()){
        com.execute(live);
    }
}

void CApplication::readFile(){
    if (!com.mapFill()){
        cout << "Error: event file was corrupted or does not exist. Import failed" << endl;
    }
}

bool CApplication :: getLive() const{
    return live;
}

void CApplication::helloMessage() const{
    cout << "\n\n\t\t\033[38;5;46;1m~ Welcome to Calendar application. To call up the command list type /help ~\n\n\n";
}

