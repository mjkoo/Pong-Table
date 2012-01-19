#include "ButtonFrame.h"

#include <assert.h>

using namespace std;

Button::Button(unsigned int row, unsigned int col,
               string label, buttoncb_t cb)
  : row_(row),
    col_(col),
    label_(label),
    cb_(cb)
{

}

Button::~Button()
{
    
}

unsigned int
Button::getRow()
{
    return row_;
}

unsigned int
Button::getCol()
{
    return col_;
}

string
Button::getLabel()
{
    return label_;
}

state_t
Button::invoke(ButtonFrame *bf, state_t currentState)
{
    return (bf->*cb_)(currentState, label_);
}

ButtonFrame::ButtonFrame(Display *display)
  : display_(display),
    currentButton_(0, 0)
{
    unsigned int row, col;

    for (row = 0; row < Display::kHeight; row++)
        for (col = 0; col < Display::kWidth; col++)
            buttons_[row][col] = NULL;
}

ButtonFrame::~ButtonFrame()
{
    unsigned int row, col;

    for (row = 0; row < Display::kHeight; row++)
        for (col = 0; col < Display::kWidth; col++)
            if (buttons_[row][col] != NULL)
                delete buttons_[row][col];
}

void
ButtonFrame::enter()
{
    unsigned int row, col;

    display_->clear();
    initializeButtons();

    for (row = 0; row < Display::kHeight; row++)
        for (col = 0; col < Display::kWidth; col++)
            if (buttons_[row][col] != NULL) {
                display_->setCursorPos(row, col);
                display_->print(buttons_[row][col]->getLabel());
            }

    for (row = 0; row < Display::kHeight; row++)
        for (col = 0; col < Display::kWidth; col++)
            if (buttons_[row][col] != NULL) {
                focusButton(row, col);
                break;
            }
}

void
ButtonFrame::exit()
{

}

Display *
ButtonFrame::getDisplay()
{
    return display_;
}

void
ButtonFrame::initializeButtons()
{

}

void
ButtonFrame::addButton(unsigned int row, unsigned int col, string label, buttoncb_t cb)
{
    assert(row < Display::kHeight);
    assert(col + label.length() < Display::kWidth);

    buttons_[row][col] = new Button(row, col, label, cb);
}

void
ButtonFrame::focusButton(unsigned int row, unsigned int col)
{
    assert(row < Display::kHeight);
    assert(col < Display::kWidth);
    assert(buttons_[row][col] != NULL);

    currentButton_.first = row;
    currentButton_.second = col;

    display_->setCursorPos(row, col);
}

void
ButtonFrame::focusNextButton(direction_t direction)
{
    int dc;
    unsigned int row, col;

    if (direction == UP) {
        col = currentButton_.second;
        for (row = currentButton_.first - 1; row >= 0; row--)
            for (dc = 1; dc < Display::kWidth; dc++) {
                if (col + dc < Display::kHeight && buttons_[row][col + dc] != NULL) {
                    focusButton(row, col + dc);
                    return;
                }
                if (col - dc >= 0 && buttons_[row][col - dc] != NULL) {
                    focusButton(row, col - dc);
                    return;
                }
            }
    } else if (direction == DOWN) {
        col = currentButton_.second;
        for (row = currentButton_.first + 1; row < Display::kHeight; row++)
            for (dc = 1; dc < Display::kWidth; dc++) {
                if (col + dc < Display::kHeight && buttons_[row][col + dc] != NULL) {
                    focusButton(row, col + dc);
                    return;
                }
                if (col - dc >= 0 && buttons_[row][col - dc] != NULL) {
                    focusButton(row, col - dc);
                    return;
                }
            }
    } else if (direction == LEFT) {
        row = currentButton_.first;
        for (col = currentButton_.second - 1; col >=0; col--)
            if (buttons_[row][col] != NULL)
                focusButton(row, col);
    } else if (direction == RIGHT) {
        row = currentButton_.first;
        for (col = currentButton_.second + 1; col < Display::kWidth; col++)
            if (buttons_[row][col] != NULL)
                focusButton(row, col);
    }
}

state_t
ButtonFrame::upButtonPressed(state_t currentState)
{
    return currentState;
}

state_t
ButtonFrame::upButtonReleased(state_t currentState)
{
    focusNextButton(UP);
    return currentState;
}

state_t
ButtonFrame::downButtonPressed(state_t currentState)
{
    return currentState;
}

state_t
ButtonFrame::downButtonReleased(state_t currentState)
{
    focusNextButton(DOWN);
    return currentState;
}

state_t
ButtonFrame::leftButtonPressed(state_t currentState)
{
    return currentState;
}

state_t
ButtonFrame::leftButtonReleased(state_t currentState)
{
    focusNextButton(LEFT);
    return currentState;
}

state_t
ButtonFrame::rightButtonPressed(state_t currentState)
{
    return currentState;
}

state_t
ButtonFrame::rightButtonReleased(state_t currentState)
{
    focusNextButton(RIGHT);
    return currentState;
}

state_t
ButtonFrame::enterButtonPressed(state_t currentState)
{
    return currentState;
}

state_t
ButtonFrame::enterButtonReleased(state_t currentState)
{
    unsigned int row, col;

    row = currentButton_.first;
    col = currentButton_.second;

    return buttons_[row][col]->invoke(this, currentState);
}

state_t
ButtonFrame::cupsChanged(state_t currentState, unsigned int numCups)
{

}

