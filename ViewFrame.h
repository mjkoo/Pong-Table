#ifndef VIEWFRAME_H_
#define VIEWFRAME_H_

#include <string>
#include <utility>

#include "Display.h"
#include "Player.h"
#include "ListFrame.h"

class ViewFrame : public ListFrame
{
public:
    ViewFrame(Display *display);
    virtual ~ViewFrame();

    void enter();
    void exit();
protected:
    void initializeList();

    state_t enterButtonReleased(state_t currentState);
};

#endif /* VIEWFRAME_H_*/
