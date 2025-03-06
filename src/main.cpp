#include "CApplication.h"
#include <stdexcept>
#include <cstdlib>

int main(){
    try {
        CApplication a;
        a.readFile();
        while (a.getLive()) {
            a.getLine();
            a.commandExecute();
        }
        a.appExit();
        return EXIT_SUCCESS;
    } catch (const runtime_error& e){
        cerr << "Exception: " << e.what() << endl;
        return EXIT_SUCCESS;
    }
}

