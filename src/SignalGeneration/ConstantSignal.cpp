#include "ConstantSignal.h"

ConstantSignal::ConstantSignal(double value)
: value(value)
{}

double ConstantSignal::generate()
{
    return value;
}

const ConstantSignal ConstantSignal::zero(0.0);