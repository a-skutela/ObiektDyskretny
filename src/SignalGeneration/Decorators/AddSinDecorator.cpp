
#include "AddSinDecorator.h"

AddSinDecorator::AddSinDecorator(std::shared_ptr<Signal> decoratedObject, double omega, double amplitude)
: SignalDecorator(decoratedObject), sinSignal(omega, amplitude)
{}

double AddSinDecorator::generate()
{
    return decoratedObject->generate() + sinSignal.generate();
}