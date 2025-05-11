#include "AddRectDecorator.h"

AddRectDecorator::AddRectDecorator(std::shared_ptr<Signal> decoratedObject, double amplitude, long period, double fillFactor)
    : SignalDecorator(decoratedObject), rectSignal(amplitude, period, fillFactor)
{
}

double AddRectDecorator::generate()
{
    return decoratedObject->generate() + rectSignal.generate();
}
