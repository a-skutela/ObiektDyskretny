#pragma once

#include "Signal.h"

class TriangleSignal : public Signal
{
    long period;
    double amplitude;
    
    long counter;
    long midpoint;
public:
    TriangleSignal(double amplitude, long period);
    
    double generate(int n) override;
};