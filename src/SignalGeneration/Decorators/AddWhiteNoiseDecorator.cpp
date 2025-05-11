#include "AddWhiteNoiseDecorator.h"

AddWhiteNoiseDecorator::AddWhiteNoiseDecorator(std::shared_ptr<Signal> decoratedObject, double amplitude)
    : SignalDecorator(decoratedObject), whiteNoiseSignal(amplitude)
{
}

double AddWhiteNoiseDecorator::generate()
{
    return decoratedObject->generate() + whiteNoiseSignal.generate();
}
