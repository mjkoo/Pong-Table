#include "TextFrame.h"

#include <boost/algorithm/string.hpp>

using namespace std;

const string TextFrame::keyboard = "abcdefghijklmnopqrstuvwxyz123456789";

TextFrame::TextFrame(Player *player)
  : ButtonFrame(player),
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
    text_ = "";
}

string
TextFrame::getText()
{
    return text_;
}

void
TextFrame::setText(const string& text)
{
    text_ = text;

    getPlayer()->getDisplay()->pushCursorPos();
    getPlayer()->getDisplay()->clearRow(kTextRow);
    getPlayer()->getDisplay()->setCursorPos(kTextRow, 0);
    getPlayer()->getDisplay()->print(text_);
    getPlayer()->getDisplay()->popCursorPos();

    if (getCursorRow() == kTextRow)
        getPlayer()->getDisplay()->setCursorPos(kTextRow, text_.size());
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

    addButton(0, 16, "DONE", static_cast<buttoncb_t>(&TextFrame::doneButtonClicked));
    addButton(kTextRow, 0, "", static_cast<buttoncb_t>(&TextFrame::backspaceButtonClicked));
    addButton(kKeyboardRow + 1, 17, "^", static_cast<buttoncb_t>(&TextFrame::shiftButtonClicked));
    addButton(kKeyboardRow + 1, 19, "_", static_cast<buttoncb_t>(&TextFrame::spaceButtonClicked));
}

void
TextFrame::toggleShift()
{
    shift_ = !shift_;
    
    getPlayer()->getDisplay()->pushCursorPos();
    getPlayer()->getDisplay()->setCursorPos(kKeyboardRow, 0);
    if (shift_)
        getPlayer()->getDisplay()->print(boost::to_upper_copy(keyboard));
    else
        getPlayer()->getDisplay()->print(keyboard);

    getPlayer()->getDisplay()->popCursorPos();
}

state_t
TextFrame::upButtonPressed(state_t currentState)
{
    state_t ret;

    ret = ButtonFrame::upButtonPressed(currentState);
    if (getCursorRow() == kTextRow)
        getPlayer()->getDisplay()->setCursorPos(kTextRow, text_.size());

    return ret;
}

state_t
TextFrame::downButtonPressed(state_t currentState)
{
    state_t ret;

    ret = ButtonFrame::downButtonPressed(currentState);
    if (getCursorRow() == kTextRow)
        getPlayer()->getDisplay()->setCursorPos(kTextRow, text_.size());

    return ret;
}

state_t
TextFrame::doneButtonClicked(state_t currentState, const string&)
{
    return currentState;
}

state_t
TextFrame::letterButtonClicked(state_t currentState, const string& label)
{
    if (text_.length() >= kMaxLength)
        return currentState;

    if (shift_)    
        text_ += boost::to_upper_copy(label);
    else
        text_ += label;

    getPlayer()->getDisplay()->pushCursorPos();
    getPlayer()->getDisplay()->clearRow(kTextRow);
    getPlayer()->getDisplay()->setCursorPos(kTextRow, 0);
    getPlayer()->getDisplay()->print(text_);
    getPlayer()->getDisplay()->popCursorPos();

    return currentState;
}

state_t
TextFrame::backspaceButtonClicked(state_t currentState, const string&)
{
    if (text_.size() == 0)
        return currentState;

    text_.erase(text_.end() - 1);
    getPlayer()->getDisplay()->setCursorPos(kTextRow, text_.size());
    getPlayer()->getDisplay()->print(" ");
    getPlayer()->getDisplay()->setCursorPos(kTextRow, text_.size());

    return currentState;
}

state_t
TextFrame::shiftButtonClicked(state_t currentState, const string&)
{
    toggleShift();
    return currentState;
}

state_t
TextFrame::spaceButtonClicked(state_t currentState, const string&)
{
    return letterButtonClicked(currentState, " ");
}
