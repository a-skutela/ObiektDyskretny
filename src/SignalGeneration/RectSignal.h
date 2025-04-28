#pragma once

#include "Signal.h"

class RectSignal : public Signal
{
    long period;
    double fillFactor;
    double amplitude;
    
    long counter;
    double levelSwitch;
public:
    RectSignal(double amplitude, long period, double fillFactor);
    
    double generate(int n) override;
};