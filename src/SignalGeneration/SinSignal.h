#pragma once

#include "Signal.h"

/**
 * \author Adrian Skutela
 * \class SinSignal
 * \brief Generates a sine wave signal.
 */
class SinSignal : public Signal
{
    int period;
    double amplitude;
    double x1;
    double x2;
    double x1Factor;
    
public:
    SinSignal(double omega, double amplitude);
    
    double generate() override;
};
