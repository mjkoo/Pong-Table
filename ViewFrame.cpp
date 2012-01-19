#include "ViewFrame.h"

#include <iostream>

using namespace std;

ViewFrame::ViewFrame(Display *display)
  : ListFrame(display)
{

}

ViewFrame::~ViewFrame()
{

}

void
ViewFrame::enter()
{
    ListFrame::enter();

    getDisplay()->setCursorPos(0, 0);
    getDisplay()->print("View Standings  DONE");
    getDisplay()->setCursorPos(0, 16);
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
