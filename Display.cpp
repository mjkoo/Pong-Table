#include "Display.h"

#include <string>

#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

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

    clear();
    setCursorPos(0, 0);
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
Display::clearRow(unsigned int row)
{
    string clearString(20, ' ');

    pushCursorPos();
    setCursorPos(row, 0);
    print(clearString);
    popCursorPos();
}

void
Display::print(string data)
{
    size_t i, len;

    /* Write the data in 16 byte chunks */
    len = data.length();
    for (i = 0; i < len; i += 16) {
        write(ttyfd_, data.substr(i, 16).c_str(), 16);
        usleep(1);
    }

    /* Determine the remaning bits by masking out len */
    write(ttyfd_, data.substr(len & 0xf0, string::npos).c_str(), len & 0x0f);
}

void
Display::setCursorPos(unsigned int row, unsigned int col)
{
    unsigned int rowOffset[4] = {0x00, 0x40, 0x14, 0x54};

    if (row >= kHeight || col >= kWidth)
        return;

    command(kSetCursorPos + rowOffset[row] + col);
    cursorPos_.first = row;
    cursorPos_.second = col;
}

void
Display::setCursorVisible(bool visible)
{

}

void
Display::setCursorBlinking(bool blinking)
{

}

void
Display::pushCursorPos()
{
    cursorStack_.push(cursorPos_);
}

void
Display::popCursorPos()
{
    cursorPos_ = cursorStack_.top();
    cursorStack_.pop();
}

void
Display::command(unsigned char cmd)
{
    writeByte(kCommand);
    writeByte(cmd);
}

void
Display::writeByte(unsigned char byte)
{
    write(ttyfd_, &byte, 1);
}
