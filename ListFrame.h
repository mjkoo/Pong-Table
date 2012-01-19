#ifndef LISTFRAME_H_
#define LISTFRAME_H_

#include <map>
#include <string>
#include <vector>

#include "Display.h"
#include "Player.h"
#include "Frame.h"

class ListFrame : public Frame
{
public:
    static const unsigned int kLines = 3;

    ListFrame(Player *player_);
    virtual ~ListFrame();

    virtual void enter();
    virtual void exit();

    Player *getPlayer();

    void append(std::string data);
    void insert(unsigned int pos, std::string data);
    void remove(unsigned int pos);
    unsigned int size();
protected:
    void refresh();
    virtual void initializeList();

    virtual state_t upButtonPressed(state_t currentState);
    virtual state_t downButtonPressed(state_t currentState);
private:
    Player *player_;
    unsigned int index_;
    std::vector<std::string> items_;
};

#endif /* LISTFRAME_H_ */
