#include "IdleFrame.h"

#include <iostream>

using namespace std;

IdleFrame::IdleFrame(Display *display)
  : ButtonFrame(display)
{

}

IdleFrame::~IdleFrame()
{

}

void
IdleFrame::enter()
{
    ButtonFrame::enter();

    getDisplay()->pushCursorPos();
    getDisplay()->setCursorPos(0, 0);
    getDisplay()->print("  Welcome to KSDA           PONG");
    getDisplay()->popCursorPos();
}

void
IdleFrame::exit()
{
    ButtonFrame::exit();
}

void
IdleFrame::initializeButtons()
{
    addButton(3, 8, string("TEST"), static_cast<buttoncb_t>(&IdleFrame::testButtonClicked));
}

state_t
IdleFrame::testButtonClicked(state_t currentState, string label)
{
    cout << label << endl;
}
