#pragma once

#include "Signal.h"

class ConstantSignal : public Signal
{
    double value;
public:
    ConstantSignal(double value);

    double generate(int n) override;
};
