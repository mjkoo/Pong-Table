#ifndef PASSWORDFRAME_H_
#define PASSWORDFRAME_H_

#include <string>

#include "Player.h"
#include "ButtonFrame.h"

class PasswordFrame : public ButtonFrame
{
public:
    static const unsigned int kPasswordLength = 5;
    static const unsigned int kPasswordRow = 2;
    static const unsigned int kPasswordCol = 4;

    PasswordFrame(Player *player);
    virtual ~PasswordFrame();

    void enter();
    void exit();
protected:
    void initializeButtons();

    void refresh();
    void enterCharacter(char c);

    state_t upButtonPressed(state_t currentState);
    state_t downButtonPressed(state_t currentState);
    state_t leftButtonPressed(state_t currentState);
    state_t rightButtonPressed(state_t currentState);

    state_t doneButtonClicked(state_t currentState, const std::string&);
private:
    std::string password_;
};

#endif /* PASSWORDFRAME_H_ */
