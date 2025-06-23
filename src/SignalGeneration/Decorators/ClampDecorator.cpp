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

const std::string ClampDecorator::type = "ClampDecorator";

std::string ClampDecorator::getType() const
{
    return ClampDecorator::type;
}

void ClampDecorator::serializeImpl(std::ostream& output) const
{
    output << minValue << " " << maxValue << " ";
}

void ClampDecorator::deserializeImpl(std::istream& input)
{
    input >> minValue >> maxValue;
}
