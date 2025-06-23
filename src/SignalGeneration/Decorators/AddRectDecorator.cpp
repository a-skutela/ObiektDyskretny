#include "AddRectDecorator.h"

AddRectDecorator::AddRectDecorator(std::shared_ptr<Signal> decoratedObject, double amplitude, long period, double fillFactor)
    : SignalDecorator(decoratedObject), rectSignal(amplitude, period, fillFactor)
{
}

double AddRectDecorator::generate()
{
    return decoratedObject->generate() + rectSignal.generate();
}

std::string AddRectDecorator::getType() const
{
    return AddRectDecorator::type;
}

const std::string AddRectDecorator::type = "AddRectDecorator";

void AddRectDecorator::serializeImpl(std::ostream& output) const
{
    rectSignal.serialize(output);
}

void AddRectDecorator::deserializeImpl(std::istream& input)
{
    rectSignal.deserialize(input);
}
