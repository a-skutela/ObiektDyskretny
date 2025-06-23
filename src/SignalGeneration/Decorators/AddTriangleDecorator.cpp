#include "AddTriangleDecorator.h"


AddTriangleDecorator::AddTriangleDecorator(std::shared_ptr<Signal> decoratedObject, double amplitude, long period)
    : SignalDecorator(decoratedObject), triangleSignal(amplitude, period)
{
}

double AddTriangleDecorator::generate()
{
    return decoratedObject->generate() + triangleSignal.generate();
}

std::string AddTriangleDecorator::getType() const
{
    return AddTriangleDecorator::type;
}

const std::string AddTriangleDecorator::type = "AddTriangleDecorator";

void AddTriangleDecorator::serializeImpl(std::ostream& output) const
{
    triangleSignal.serialize(output);
}

void AddTriangleDecorator::deserializeImpl(std::istream& input)
{
    triangleSignal.deserialize(input);
}
