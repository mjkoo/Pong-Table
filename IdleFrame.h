#ifndef IDLEFRAME_H_
#define IDLEFRAME_H_

#include <string>

#include "Player.h"
#include "ButtonFrame.h"

class IdleFrame : public ButtonFrame
{
public:
    IdleFrame(Player *player);
    virtual ~IdleFrame();

    void enter();
    void exit();
protected:
    void initializeButtons();

    state_t loginButtonClicked(state_t currentState, std::string label);
    state_t createButtonClicked(state_t currentState, std::string label);
    state_t viewButtonClicked(state_t currentState, std::string label);
    state_t testButtonClicked(state_t currentState, std::string label);
};

#endif /* IDLEFRAME_H_*/
