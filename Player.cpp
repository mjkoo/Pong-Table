#include "Player.h"

//TEMP
#include <iostream>
#define CONSOLE

#include <utility>

#include <assert.h>
#include <unistd.h>

#include "CreateFrame.h"
#include "ErrorFrame.h"
#include "IdleFrame.h"
#include "LoginFrame.h"
#include "PasswordFrame.h"
#include "ViewFrame.h"

using namespace std;

namespace {
    unsigned int
    countBits(unsigned int v)
    {
        /* From http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan */
        unsigned int c;
        for (c = 0; v; c++) {
            v &= v - 1;
        }

        return c;
    }
}

Player::Player(int serialDevice, string databaseFile)
  : currentState_(kNoneState),
    currentFrame_(NULL),
    stateMap_(),
    serialDevice_(serialDevice),
    display_(Display(serialDevice)),
    database_(Database(databaseFile)),
    name_(),
    thread_(),
    other_(NULL),
    cupCount_(0)
{
    stateMap_.insert(pair<state_t, Frame *>(kIdleState, new IdleFrame(this)));
    stateMap_.insert(pair<state_t, Frame *>(kLoginState, new LoginFrame(this)));
    stateMap_.insert(pair<state_t, Frame *>(kCreateState, new CreateFrame(this)));
    stateMap_.insert(pair<state_t, Frame *>(kViewState, new ViewFrame(this)));
    stateMap_.insert(pair<state_t, Frame *>(kLoginPasswordState, new PasswordFrame(this)));
    stateMap_.insert(pair<state_t, Frame *>(kCreatePasswordState, new PasswordFrame(this)));
    stateMap_.insert(pair<state_t, Frame *>(kErrorState, new ErrorFrame(this)));
}

Player::~Player()
{
    map<state_t, Frame *>::iterator it;
    for (it = stateMap_.begin(); it != stateMap_.end(); ++it)
        delete it->second;
}

Display *
Player::getDisplay()
{
    return &display_;
}

Database *
Player::getDatabase()
{
    return &database_;
}

string
Player::getName()
{
    return name_;
}

void
Player::setName(string name)
{
    name_ = name;
}

void
Player::error(string msg, state_t returnState)
{
    ErrorFrame *ef;
    map<state_t, Frame *>::iterator it;

    it = stateMap_.find(kErrorState);
    if (it == stateMap_.end())
        return;

    ef = static_cast<ErrorFrame *>(it->second);
    ef->error(msg, returnState);
    changeState(kErrorState);
}

void
Player::changeState(state_t nextState)
{
    map<state_t, Frame *>::iterator it;

    if (nextState == currentState_)
        return;

    it = stateMap_.find(nextState);
    if (it == stateMap_.end())
        return;

    if (currentFrame_ != NULL)
        currentFrame_->exit();

    currentState_ = nextState;
    currentFrame_ = it->second;
    currentFrame_->enter();
}

void
Player::run()
{
    unsigned short currentInput, lastInput = 0;

    changeState(kIdleState);
    while (1)
    {
#ifdef CONSOLE
        cin >> hex >> currentInput;
#else
        while (read(serialDevice_, &currentInput, sizeof(unsigned short)) == 0)
            ;
#endif
        cout << currentInput << endl;

        /* Check for cup state change */
        if ((lastInput & kCupMask) != (currentInput & kCupMask))
            changeState(currentFrame_->cupsChanged(currentState_,
                countBits(currentInput & kCupMask)));

        /* Check for enter key press */
        if ((lastInput & kEnterMask) && !(currentInput & kEnterMask))
            changeState(currentFrame_->enterButtonReleased(currentState_));
        if ((currentInput & kEnterMask) && !(lastInput & kEnterMask))
            changeState(currentFrame_->enterButtonPressed(currentState_));

        /* Check for button releases */
        if (lastInput & kUpMask)
            changeState(currentFrame_->upButtonReleased(currentState_));
        if (lastInput & kDownMask)
            changeState(currentFrame_->downButtonReleased(currentState_));
        if (lastInput & kLeftMask)
            changeState(currentFrame_->leftButtonReleased(currentState_));
        if (lastInput & kRightMask)
            changeState(currentFrame_->rightButtonReleased(currentState_));

        /* Check for button releases */
        if (currentInput & kUpMask)
            changeState(currentFrame_->upButtonPressed(currentState_));
        if (currentInput & kDownMask)
            changeState(currentFrame_->downButtonPressed(currentState_));
        if (currentInput & kLeftMask)
            changeState(currentFrame_->leftButtonPressed(currentState_));
        if (currentInput & kRightMask)
            changeState(currentFrame_->rightButtonPressed(currentState_));

        lastInput = currentInput;
    }
}
