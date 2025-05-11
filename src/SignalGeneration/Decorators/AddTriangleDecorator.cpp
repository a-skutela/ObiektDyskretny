#include "AddTriangleDecorator.h"

AddTriangleDecorator::AddTriangleDecorator(std::shared_ptr<Signal> decoratedObject, double amplitude, long period)
    : SignalDecorator(decoratedObject), triangleSignal(amplitude, period)
{
}

double AddTriangleDecorator::generate()
{
    return decoratedObject->generate() + triangleSignal.generate();
}
