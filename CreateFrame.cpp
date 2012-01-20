#include "CreateFrame.h"

#include <iostream>

using namespace std;

CreateFrame::CreateFrame(Player *player)
  : TextFrame(player)
{

}

CreateFrame::~CreateFrame()
{

}

void
CreateFrame::enter()
{
    TextFrame::enter();

    getPlayer()->getDisplay()->pushCursorPos();
    getPlayer()->getDisplay()->setCursorPos(0, 0);
    getPlayer()->getDisplay()->print("Create");
    getPlayer()->getDisplay()->popCursorPos();
}

void
CreateFrame::exit()
{
    TextFrame::exit();
}

state_t
CreateFrame::doneButtonClicked(state_t currentState, string label)
{
    getPlayer()->setName(getText());
    cout << getPlayer()->getName() << endl;
    return kCreatePasswordState;
}

