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
    enum {
        kLines = 3
    };

    ListFrame(Display *display);
    virtual ~ListFrame();

    virtual void enter();
    virtual void exit();

    Display *getDisplay();

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
    Display *display_;
    unsigned int index_;
    std::vector<std::string> items_;
};

#endif /* LISTFRAME_H_ */
