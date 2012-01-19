#include "IdleFrame.h"

#include <iostream>

using namespace std;

IdleFrame::IdleFrame(Player *player)
  : ButtonFrame(player)
{

}

IdleFrame::~IdleFrame()
{

}

void
IdleFrame::enter()
{
    ButtonFrame::enter();

    getPlayer()->getDisplay()->pushCursorPos();
    getPlayer()->getDisplay()->setCursorPos(0, 0);
    getPlayer()->getDisplay()->print("  Welcome to KSDA        PONG TABLE");
    getPlayer()->getDisplay()->popCursorPos();
}

void
IdleFrame::exit()
{
    ButtonFrame::exit();
}

void
IdleFrame::initializeButtons()
{
    addButton(2, 8, string("LOGIN"), static_cast<buttoncb_t>(&IdleFrame::loginButtonClicked));
    addButton(3, 0, string("MUSIC"), static_cast<buttoncb_t>(&IdleFrame::testButtonClicked));
    addButton(3, 8, string("CREATE"), static_cast<buttoncb_t>(&IdleFrame::testButtonClicked));
    addButton(3, 16, string("VIEW"), static_cast<buttoncb_t>(&IdleFrame::viewButtonClicked));
}

state_t
IdleFrame::loginButtonClicked(state_t currentState, string label)
{
    return kLoginState;
}

state_t
IdleFrame::viewButtonClicked(state_t currentState, string label)
{
    return kViewState;
}

state_t
IdleFrame::testButtonClicked(state_t currentState, string label)
{
    cout << label << endl;
}
