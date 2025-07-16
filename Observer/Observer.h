#pragma once


class Observer {
public:
    virtual void updateObserver() = 0;

    virtual ~Observer() = default;
};