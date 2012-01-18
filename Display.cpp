#include "Display.h"

#include <cstring>
#include <string>

#include <termios.h>
#include <fcntl.h>

using namespace std;

Display::Display(string dev)
  : ttyfd_(0),
    cursorStack_()
{
    /* TTY initialization from http://en.wikibooks.org/wiki/Serial_Programming/Serial_Linux */
    struct termios tio;

    ttyfd_ = open(dev.c_str(), O_RDWR | O_NONBLOCK);

    memset(&tio, 0, sizeof(tio));
    tio.c_iflag = 0;
    tio.c_oflag = 0;
    tio.c_cflag = CS8 | CREAD | CLOCAL;
    tio.c_lflag = 0;
    tio.c_cc[VMIN] = 1;
    tio.c_cc[VTIME] = 0;
    
    cfsetospeed(&tio, B9600);
    cfsetispeed(&tio, B9600);
    tcsetattr(ttyfd_, TCSANOW, &tio);
}

Display::~Display()
{
    close(ttyfd_);
}

void
Display::clear()
{
    writeByte(kCommand);
    writeByte(kClear);
}

void
Display::print(string data)
{
    write(ttyfd_, data.c_str(), data.length());
}

void
Display::writeByte(unsigned char byte)
{
    write(ttyfd_, &byte, 1);
}
