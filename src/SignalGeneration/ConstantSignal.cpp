#include "ConstantSignal.h"

ConstantSignal::ConstantSignal(double value)
: value(value)
{}

double ConstantSignal::generate(int n)
{
    return value;
}