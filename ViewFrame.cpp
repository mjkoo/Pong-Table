#include "ViewFrame.h"

#include <iostream>

using namespace std;

ViewFrame::ViewFrame(Player *player)
  : ListFrame(player)
{

}

ViewFrame::~ViewFrame()
{

}

void
ViewFrame::enter()
{
    ListFrame::enter();

    getPlayer()->getDisplay()->setCursorPos(0, 0);
    getPlayer()->getDisplay()->print("View Standings  DONE");
    getPlayer()->getDisplay()->setCursorPos(0, 16);
}

void
ViewFrame::exit()
{
    ListFrame::exit();
}

void
ViewFrame::initializeList()
{
    append("Hello");
    append("World");
    append("This");
    append("Is");
    append("A");
    append("Test");
}

state_t
ViewFrame::enterButtonReleased(state_t currentState)
{
    return kIdleState;
}
