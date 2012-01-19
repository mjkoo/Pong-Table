#include "ListFrame.h"

#include <assert.h>

using namespace std;

ListFrame::ListFrame(Display *display)
  : display_(display),
    index_(0),
    items_()
{

}

ListFrame::~ListFrame()
{

}

void
ListFrame::enter()
{
    unsigned int i;

    display_->clear();
    initializeList();
    refresh();
}

void
ListFrame::exit()
{

}

Display *
ListFrame::getDisplay()
{
    return display_;
}

void
ListFrame::append(string data)
{
    assert(data.length() <= Display::kWidth);
    items_.push_back(data);
}

void
ListFrame::insert(unsigned int pos, string data)
{
    assert(data.length() <= Display::kWidth);
    assert(pos <= items_.size());
    
    vector<string>::iterator it = items_.begin() + pos;
    items_.insert(it, data);
}

void
ListFrame::remove(unsigned int pos)
{
    assert(pos < items_.size());
    vector<string>::iterator it = items_.begin() + pos;
    items_.erase(it);
}

unsigned int
ListFrame::size()
{
    return items_.size();
}

void
ListFrame::refresh()
{
    unsigned int i, len;

    len = (items_.size() < kLines) ? items_.size() : kLines;
    display_->pushCursorPos();
    for (i = 0; i < len; i++) {
        display_->clearRow(i + 1);
        display_->setCursorPos(i + 1, 0);
        display_->print(items_[(index_ + i) % items_.size()]);
    }
    display_->popCursorPos();
}

void
ListFrame::initializeList()
{

}

state_t
ListFrame::upButtonPressed(state_t currentState)
{
    if (index_ > 0) {
        index_--;
        refresh();
    }
    return currentState;
}

state_t
ListFrame::downButtonPressed(state_t currentState)
{
    if (index_ < items_.size() - 3) {
        index_++;
        refresh();
    }
    return currentState;
}

