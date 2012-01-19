/* TTY initialization from http://en.wikibooks.org/wiki/Serial_Programming/Serial_Linux
 * SerLCD functions referenced from http://arduino.cc/playground/Code/SerLCD
 */
#include "Display.h"

//TEMP
#include <iostream>

#include <assert.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>

using namespace std;

Display::Display(string dev)
  : ttyfd_(0),
    cursorPos_(0, 0),
    cursorStack_()
{
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
    write(ttyfd_, data.c_str(), data.length());
    return;
}

void
Display::setCursorPos(unsigned int row, unsigned int col)
{
    unsigned int rowOffset[4] = {0x00, 0x40, 0x14, 0x54};

    assert(row < kHeight);
    assert(col < kWidth);

    command(kSetCursorPos + rowOffset[row] + col);
    cursorPos_.first = row;
    cursorPos_.second = col;
}

void
Display::setCursorVisible(bool visible)
{
    command(visible ? kCursorOn : kCursorOff);
}

void
Display::pushCursorPos()
{
    cursorStack_.push(cursorPos_);
}

void
Display::popCursorPos()
{
    pair<unsigned int, unsigned int> pos;

    pos = cursorStack_.top();
    setCursorPos(pos.first, pos.second);

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
