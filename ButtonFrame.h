#ifndef BUTTONFRAME_H_
#define BUTTONFRAME_H_

#include <map>
#include <string>
#include <utility>

#include "Display.h"
#include "Player.h"
#include "Frame.h"

class ButtonFrame;
typedef state_t (ButtonFrame::*buttoncb_t) (state_t currentState, std::string label);

enum direction_t
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Button
{
public:
    friend class ButtonFrame;

    Button(unsigned int row, unsigned int col, std::string label, buttoncb_t cb);
    virtual ~Button();

    unsigned int getRow();
    unsigned int getCol();
    std::string getLabel();

    state_t invoke(ButtonFrame *bf, state_t currentState);
private:
    unsigned int row_, col_;
    std::string label_;
    buttoncb_t cb_;
};

class ButtonFrame : public Frame
{
public:
    ButtonFrame(Display *display);
    virtual ~ButtonFrame();

    virtual void enter();
    virtual void exit();

    Display *getDisplay();
protected:
    virtual void initializeButtons();
    void addButton(unsigned int row, unsigned int col, std::string label, buttoncb_t cb);
    void focusButton(unsigned int row, unsigned int col);
    void focusNextButton(direction_t direction);

    virtual state_t upButtonPressed(state_t currentState);
    virtual state_t downButtonPressed(state_t currentState);
    virtual state_t leftButtonPressed(state_t currentState);
    virtual state_t rightButtonPressed(state_t currentState);
    virtual state_t enterButtonReleased(state_t currentState);
private:
    Display *display_;
    Button *buttons_[Display::kHeight][Display::kWidth];
    std::pair<unsigned int, unsigned int> currentButton_;
};

#endif /* BUTTONFRAME_H_ */
