#include "Player.h"

int
main(int argc, char **argv)
{
    Player player("/dev/ttyO1", "test.db");
    player.run();

    return 0;
}
