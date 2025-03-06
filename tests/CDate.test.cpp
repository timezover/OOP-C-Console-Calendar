#include <cassert>
#include "CDate.h"

int main(){
    assert(calculateDay("31.05.2023") == "Wednesday");

    assert(calculateDay("10.04.2023") == "Monday");

    assert(calculateDay("20.08.2021") == "Friday");

    assert(!dateValid("wgfwargaerg"));

    assert(!dateValid("10.05.20000"));

    assert(dateValid("01.01.2023"));

    assert(!dateValid("10.100.2017"));
}