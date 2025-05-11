#include "ClampDecorator.h"
#include <algorithm>

ClampDecorator::ClampDecorator(std::shared_ptr<Signal> decoratedObject, double minValue, double maxValue)
    : SignalDecorator(decoratedObject), minValue(minValue), maxValue(maxValue) {}

double ClampDecorator::generate()
{
    double value = decoratedObject->generate();
    if (value <= minValue)
    {
        return minValue;
    }
    else if (value >= maxValue)
    {
        return maxValue;
    }
    else
    {
        return value;
    }
}
