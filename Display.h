#ifndef DISPLAY_H
#define DISPLAY_H

#include <stack>
#include <string>

class Display
{
public:
    enum {
        kHeight = 4,
        kWidth = 20,
        kCommand = 0xfe,
        kClear = 0x01,
        kSetCursorPos = 0x80,
        kCursorOn = 0x0d,
        kCursorOff = 0x0c
    };

    Display(std::string dev);
    virtual ~Display();

    void clear();
    void clearRow(unsigned int row);
    void print(std::string data);

    void setCursorPos(unsigned int row, unsigned int col);
    void setCursorVisible(bool visible);
    void pushCursorPos();
    void popCursorPos();
private:
    void command(unsigned char cmd);
    void writeByte(unsigned char byte);

    int ttyfd_;
    std::pair<unsigned int, unsigned int> cursorPos_;
    std::stack<std::pair<unsigned int, unsigned int> > cursorStack_;
};

#endif /* DISPLAY_H_ */
