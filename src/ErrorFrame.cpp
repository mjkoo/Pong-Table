#include "ErrorFrame.h"

using namespace std;

ErrorFrame::ErrorFrame(Player *player)
  : ButtonFrame(player),
    returnState_(kIdleState),
    msg_()
{

}

ErrorFrame::~ErrorFrame()
{

}

void
ErrorFrame::enter()
{
    ButtonFrame::enter();

    getPlayer()->getDisplay()->pushCursorPos();
    getPlayer()->getDisplay()->setCursorPos(kErrorRow, 0);
    getPlayer()->getDisplay()->print("Error: " + msg_);
    getPlayer()->getDisplay()->popCursorPos();
}

void
ErrorFrame::exit()
{
    ButtonFrame::exit();
}

void
ErrorFrame::error(string msg, state_t returnState)
{
    msg_ = msg;
    returnState_ = returnState;
}

void
ErrorFrame::initializeButtons()
{
    addButton(3, 8, string("OK"), static_cast<buttoncb_t>(&ErrorFrame::okButtonClicked));
}

state_t
ErrorFrame::okButtonClicked(state_t, const string&)
{
    return returnState_;
}

