#ifndef LOGINFRAME_H_
#define LOGINFRAME_H_

#include <string>
#include <utility>

#include "Display.h"
#include "Player.h"
#include "TextFrame.h"

class LoginFrame : public TextFrame
{
public:
    LoginFrame(Player *player);
    virtual ~LoginFrame();

    void enter();
    void exit();
protected:
    state_t doneButtonClicked(state_t currentState, std::string label);
};

#endif /* LOGINFRAME_H_*/
