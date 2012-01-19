#include <iostream>

#include <sqlite.h>

#include "Display.h"
#include "Player.h"

using namespace std;

int
main(int argc, char **argv)
{
    Display disp("/dev/ttyO1");

    disp.clear();
    disp.setCursorVisible(true);
    disp.print("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyza");

    Player player(&disp);
    player.run();

    return 0;
}
