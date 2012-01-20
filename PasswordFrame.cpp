#include "PasswordFrame.h"

#include <iostream>

using namespace std;

PasswordFrame::PasswordFrame(Player *player)
  : ButtonFrame(player),
    password_()
{

}

PasswordFrame::~PasswordFrame()
{

}

void
PasswordFrame::enter()
{
    ButtonFrame::enter();
    
    getPlayer()->getDisplay()->pushCursorPos();
    getPlayer()->getDisplay()->setCursorPos(0, 0);
    getPlayer()->getDisplay()->print("Password");
    getPlayer()->getDisplay()->popCursorPos();

    refresh();
}

void
PasswordFrame::exit()
{
    ButtonFrame::exit();
    password_ = "";
}

void
PasswordFrame::initializeButtons()
{
    addButton(0, 16, string("DONE"), static_cast<buttoncb_t>(&PasswordFrame::doneButtonClicked));
}

void
PasswordFrame::refresh()
{
    unsigned int i;

    getPlayer()->getDisplay()->pushCursorPos();
    getPlayer()->getDisplay()->setCursorPos(kPasswordRow, kPasswordCol);
    for (i = 0; i < kPasswordLength; i++)
        if (i < password_.length())
            getPlayer()->getDisplay()->print(string(1, password_[i]) + " ");
        else
            getPlayer()->getDisplay()->print("_ ");
    getPlayer()->getDisplay()->popCursorPos();
}

void
PasswordFrame::enterCharacter(char c)
{
    if (password_.length() >= kPasswordLength)
        return;

    password_ += c;
    refresh();
}

state_t
PasswordFrame::upButtonPressed(state_t currentState)
{
    enterCharacter('u');
    return currentState;
}

state_t
PasswordFrame::downButtonPressed(state_t currentState)
{
    enterCharacter('d');
    return currentState;
}

state_t
PasswordFrame::leftButtonPressed(state_t currentState)
{
    enterCharacter('l');
    return currentState;
}

state_t
PasswordFrame::rightButtonPressed(state_t currentState)
{
    enterCharacter('r');
    return currentState;
}

state_t
PasswordFrame::doneButtonClicked(state_t currentState, string label)
{
    if (password_.length() < kPasswordLength)
        return currentState;

    cout << "Username: " << getPlayer()->getName() << " Password: " << password_ << endl;

    if (currentState == kLoginPasswordState)
        cout << getPlayer()->getDatabase()->login(getPlayer()->getName(), password_) << endl;
    else if (currentState == kCreatePasswordState)
        cout << getPlayer()->getDatabase()->create(getPlayer()->getName(), password_) << endl;

    return kIdleState;
}
