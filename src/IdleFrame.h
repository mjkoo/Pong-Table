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

    state_t loginButtonClicked(state_t, const std::string&);
    state_t createButtonClicked(state_t, const std::string&);
    state_t viewButtonClicked(state_t, const std::string&);
};

#endif /* IDLEFRAME_H_*/
