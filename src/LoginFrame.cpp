#include "LoginFrame.h"

#include <iostream>

using namespace std;

LoginFrame::LoginFrame(Player *player)
  : TextFrame(player)
{

}

LoginFrame::~LoginFrame()
{

}

void
LoginFrame::enter()
{
    TextFrame::enter();

    getPlayer()->getDisplay()->pushCursorPos();
    getPlayer()->getDisplay()->setCursorPos(0, 0);
    getPlayer()->getDisplay()->print("Login");
    getPlayer()->getDisplay()->popCursorPos();
}

void
LoginFrame::exit()
{
    TextFrame::exit();
}

state_t
LoginFrame::doneButtonClicked(state_t currentState, const string&)
{
    if (getText().length() == 0)
        return currentState;

    getPlayer()->setName(getText());
    cout << getPlayer()->getName() << endl;
    return kLoginPasswordState;
}

