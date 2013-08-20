#include <iostream>
using std::cout;
using std::endl;

#include "libll++/obstack.h"

int main()
{
    ll::obstack ob;
    long i = 1;
    long *p = &i;

    ob.grow(i);
    long *p2 = (long*)ob.finish();
    cout << *p2 << endl;

    ob.grow(p);
    p2 = (long*)ob.finish();
    cout << *p2 << endl;

    return 0;
}

