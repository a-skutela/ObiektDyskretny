#pragma once

#include "Signal.h"

class SinSignal : public Signal
{
    int period;
    double amplitude;
    double x1;
    double x2;
    double x1Factor;
    
public:
    SinSignal(double omega, double amplitude);
    
    double generate(int n) override;
};
