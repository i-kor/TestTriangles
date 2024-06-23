#pragma once

// Machine state for reading input line by line
enum class State
{
    FirstTriangle,
    SecondTriangle,
    ExpectedResult
};

// State wraper to provide init and next
class StateWrapper
{
    State state;
public:
    StateWrapper(): state{ State::FirstTriangle } {}

    void Next()
    {
        if(state == State::FirstTriangle )
            state = State::SecondTriangle;
        else if(state == State::SecondTriangle)
            state = State::ExpectedResult;
        else
            state = State::FirstTriangle;
    }

    operator State() { return state; }
};