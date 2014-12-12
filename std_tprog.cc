#include <iostream>
#include "std_template_buffer.h"

//g++ -v std_tprog.cc

using namespace std;

int
main ()
{
    Buffer<float> f(10);
    f.insert (0.25);
    f.insert (1.0 + f.get(0));
    cout << "stored value = " << f.get(0) << endl;
    return 0;
}
