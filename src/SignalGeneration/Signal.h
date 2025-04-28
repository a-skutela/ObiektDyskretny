#pragma once

class Signal
{
public:
    virtual double generate(int n) = 0;

    virtual ~Signal() = default;
};