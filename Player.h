#ifndef PLAYER_H_
#define PLAYER_H_

#include <map>

#include "Display.h"

class Frame;

enum state_t
{
    kIdleState,
    kLoginState,
    kCreateState,
    kViewState,
    kMusicState,
    kPasswordState,
    kWaitingState,
    kLosingState,
    kTiedState,
    kWinningState,
    kOverState,
    kNoneState
};

class Player
{
public:
    enum {
        kUpMask = 0x4000,
        kDownMask = 0x2000,
        kLeftMask = 0x1000,
        kRightMask = 0x0800,
        kEnterMask = 0x0400,
        kCupMask = 0x03ff
    };

    Player(Display *display);
    virtual ~Player();

    void run();
private:
    void changeState(state_t nextState);

    state_t currentState_;
    Frame *currentFrame_;
    std::map<state_t, Frame *> stateMap_;
};

#endif /* Player_H_ */
