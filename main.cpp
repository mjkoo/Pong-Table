#include <iostream>

#include <sqlite.h>

#include <Display.h>

using namespace std;

int
main(int argc, char **argv)
{
    Display disp("/dev/ttyO1");

    disp.clear();
    disp.print("Hello World");

    return 0;
}
