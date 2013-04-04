#ifndef CREATEFRAME_H_
#define CREATEFRAME_H_

#include <string>
#include <utility>

#include "Display.h"
#include "Player.h"
#include "TextFrame.h"

class CreateFrame : public TextFrame
{
public:
    CreateFrame(Player *player);
    virtual ~CreateFrame();

    void enter();
    void exit();
protected:
    state_t doneButtonClicked(state_t currentState, const std::string&);
};

#endif /* CREATEFRAME_H_*/
