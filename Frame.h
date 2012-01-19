#ifndef FRAME_H_
#define FRAME_H_

#include "Player.h"

class Frame
{
public:
    virtual void enter() = 0;
    virtual void exit() = 0;

    virtual state_t upButtonPressed(state_t currentState) = 0;
    virtual state_t upButtonReleased(state_t currentState) = 0;
    virtual state_t downButtonPressed(state_t currentState) = 0;
    virtual state_t downButtonReleased(state_t currentState) = 0;
    virtual state_t leftButtonPressed(state_t currentState) = 0;
    virtual state_t leftButtonReleased(state_t currentState) = 0;
    virtual state_t rightButtonPressed(state_t currentState) = 0;
    virtual state_t rightButtonReleased(state_t currentState) = 0;
    virtual state_t enterButtonPressed(state_t currentState) = 0;
    virtual state_t enterButtonReleased(state_t currentState) = 0;

    virtual state_t cupsChanged(state_t currentState, unsigned int numCups) = 0;
};

#endif /* FRAME_H_ */
