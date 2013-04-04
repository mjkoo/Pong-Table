/* TTY initialization from http://en.wikibooks.org/wiki/Serial_Programming/Serial_Linux
 * SerLCD functions referenced from http://arduino.cc/playground/Code/SerLCD
 */
#include "Display.h"

#include <unistd.h>
#include <assert.h>

using namespace std;

Display::Display(int ttyfd)
  : ttyfd_(ttyfd),
    cursorPos_(0, 0),
    cursorStack_()
{
    clear();
    setCursorPos(0, 0);
    setCursorVisible(true);
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
