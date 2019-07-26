#ifndef STATE_HPP_
#define STATE_HPP_

struct State {
    bool valveOpen = false;
    bool displayDimmed = false;
    bool dirty = false;
};

extern struct State state;

#endif