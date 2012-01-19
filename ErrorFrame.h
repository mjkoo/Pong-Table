#ifndef ERRORFRAME_H_
#define ERRORFRAME_H_

#include <string>
#include <utility>

#include "Display.h"
#include "Player.h"
#include "ButtonFrame.h"

class ErrorFrame : public ButtonFrame
{
public:
    static const unsigned int kErrorRow = 1;

    ErrorFrame(Player *player);
    virtual ~ErrorFrame();

    void enter();
    void exit();

    void error(std::string msg, state_t returnState);
protected:
    void initializeButtons();

    state_t okButtonClicked(state_t currentState, std::string label);
private:
    state_t returnState_;
    std::string msg_;
};

#endif /* ERRORFRAME_H_*/
