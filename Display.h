#ifndef DISPLAY_H
#define DISPLAY_H

#include <stack>
#include <string>

class Display
{
public:
    static const unsigned int kHeight = 4;
    static const unsigned int kWidth = 20;
    static const unsigned int kCommand = 0xfe;
    static const unsigned int kClear = 0x01;
    static const unsigned int kSetCursorPos = 0x80;
    static const unsigned int kCursorOn = 0x0d;
    static const unsigned int kCursorOff = 0x0c;

    Display(int ttyfd);
    virtual ~Display();

    void clear();
    void clearRow(unsigned int row);
    void print(const std::string& data);

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
