#include <fcntl.h>
#include <string.h>
#include <termios.h>

#include "Player.h"

int
main(int argc, char **argv)
{
    int ttyfd;
    struct termios tio;

    ttyfd = open("/dev/ttyO1", O_RDWR | O_NOCTTY | O_NDELAY);

    tcgetattr(ttyfd, &tio);
    tio.c_cflag &= ~PARENB;
    tio.c_cflag &= ~CSTOPB;
    tio.c_cflag &= ~CSIZE;
    tio.c_cflag &= ~CRTSCTS;
    tio.c_cflag |= CS8 | CREAD | CLOCAL;
    tio.c_lflag &= ~(ICANON | ECHO | ISIG);
    
    cfsetospeed(&tio, B9600);
    cfsetispeed(&tio, B9600);
    tcsetattr(ttyfd, TCSANOW, &tio);

    Player player(ttyfd, "test.db");
    player.run();

    return 0;
}
