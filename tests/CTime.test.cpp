#include <cassert>
#include "CTime.h"

int main(){
    CTime t1("00:00");
    assert(t1.timeValid());

    CTime t2("100:100");
    assert(!t2.timeValid());

    assert(checkOrder("10:00", "12:00"));

    assert(!checkOrder("11:30", "11:29"));
}