#include "ListFrame.h"

#include <assert.h>

using namespace std;

ListFrame::ListFrame(Player *player)
  : player_(player),
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
    player_->getDisplay()->clear();
    initializeList();
    refresh();
}

void
ListFrame::exit()
{

}

Player *
ListFrame::getPlayer()
{
    return player_;
}

void
ListFrame::append(const string& data)
{
    assert(data.length() <= Display::kWidth);
    items_.push_back(data);
    refresh();
}

void
ListFrame::insert(unsigned int pos, const string& data)
{
    assert(data.length() <= Display::kWidth);
    assert(pos <= items_.size());
    
    vector<string>::iterator it = items_.begin() + pos;
    items_.insert(it, data);
    refresh();
}

void
ListFrame::remove(unsigned int pos)
{
    assert(pos < items_.size());
    vector<string>::iterator it = items_.begin() + pos;
    items_.erase(it);
    refresh();
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
    player_->getDisplay()->pushCursorPos();
    for (i = 0; i < len; i++) {
        player_->getDisplay()->clearRow(i + 1);
        player_->getDisplay()->setCursorPos(i + 1, 0);
        player_->getDisplay()->print(items_[(index_ + i) % items_.size()]);
    }
    player_->getDisplay()->popCursorPos();
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

