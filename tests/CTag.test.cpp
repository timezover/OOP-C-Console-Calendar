#include "CTag.h"
#include <cassert>

int main(){
    CTag t1("#testing    #TEEESTING");
    assert(t1.tagValid());

    CTag t2("#wow  #omg  &oops");
    assert(!t2.tagValid());

    CTag t3("#OmGUwU                     #TAG");
    assert(t3.tagValid());
}
