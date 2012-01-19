#include "TextFrame.h"

#include <boost/algorithm/string.hpp>

using namespace std;

const string TextFrame::keyboard = "abcdefghijklmnopqrstuvwxyz123456789";

TextFrame::TextFrame(Display *display)
  : ButtonFrame(display),
    text_(),
    shift_(false)
{

}

TextFrame::~TextFrame()
{

}

void
TextFrame::enter()
{
    ButtonFrame::enter();
    focusButton(kKeyboardRow, 0);
}

void
TextFrame::exit()
{
    ButtonFrame::exit();
}

string
TextFrame::getText()
{
    return text_;
}

void
TextFrame::setText(string text)
{
    text_ = text;

    getDisplay()->pushCursorPos();
    getDisplay()->clearRow(kTextRow);
    getDisplay()->setCursorPos(kTextRow, 0);
    getDisplay()->print(text_);
    getDisplay()->popCursorPos();

    if (getCursorRow() == kTextRow)
        getDisplay()->setCursorPos(kTextRow, text_.size());
}

void
TextFrame::initializeButtons()
{
    unsigned int row = kKeyboardRow, col = 0;
    string::const_iterator it;
    
    for (it = keyboard.begin(); it != keyboard.end(); ++it) {
        addButton(row, col, string(1, *it), static_cast<buttoncb_t>(&TextFrame::letterButtonClicked));
        if (++col >= Display::kWidth) {
            row++;
            col = 0;
        }
    }

    addButton(0, 16, string("DONE"), static_cast<buttoncb_t>(&TextFrame::doneButtonClicked));
    addButton(kTextRow, 0, string(), static_cast<buttoncb_t>(&TextFrame::backspaceButtonClicked));
    addButton(kKeyboardRow + 1, 17, "^", static_cast<buttoncb_t>(&TextFrame::shiftButtonClicked));
    addButton(kKeyboardRow + 1, 19, "_", static_cast<buttoncb_t>(&TextFrame::spaceButtonClicked));
}

void
TextFrame::toggleShift()
{
    shift_ = !shift_;
    
    getDisplay()->pushCursorPos();
    getDisplay()->setCursorPos(kKeyboardRow, 0);
    if (shift_)
        getDisplay()->print(boost::to_upper_copy(keyboard));
    else
        getDisplay()->print(keyboard);

    getDisplay()->popCursorPos();
}

state_t
TextFrame::upButtonPressed(state_t currentState)
{
    state_t ret;

    ret = ButtonFrame::upButtonPressed(currentState);
    if (getCursorRow() == kTextRow)
        getDisplay()->setCursorPos(kTextRow, text_.size());

    return ret;
}

state_t
TextFrame::downButtonPressed(state_t currentState)
{
    state_t ret;

    ret = ButtonFrame::downButtonPressed(currentState);
    if (getCursorRow() == kTextRow)
        getDisplay()->setCursorPos(kTextRow, text_.size());

    return ret;
}

state_t
TextFrame::doneButtonClicked(state_t currentState, string label)
{
    return currentState;
}

state_t
TextFrame::letterButtonClicked(state_t currentState, string label)
{
    if (text_.length() >= kMaxLength)
        return currentState;

    if (shift_)    
        text_ += boost::to_upper_copy(label);
    else
        text_ += label;

    getDisplay()->pushCursorPos();
    getDisplay()->clearRow(kTextRow);
    getDisplay()->setCursorPos(kTextRow, 0);
    getDisplay()->print(text_);
    getDisplay()->popCursorPos();

    return currentState;
}

state_t
TextFrame::backspaceButtonClicked(state_t currentState, string label)
{
    if (text_.size() == 0)
        return currentState;

    text_.erase(text_.end() - 1);
    getDisplay()->setCursorPos(kTextRow, text_.size());
    getDisplay()->print(" ");
    getDisplay()->setCursorPos(kTextRow, text_.size());

    return currentState;
}

state_t
TextFrame::shiftButtonClicked(state_t currentState, string label)
{
    toggleShift();
    return currentState;
}

state_t
TextFrame::spaceButtonClicked(state_t currentState, string label)
{
    return letterButtonClicked(currentState, " ");
}
