#include "AddConstantDecorator.h"

AddConstantDecorator::AddConstantDecorator(std::shared_ptr<Signal> decoratedObject, double value)
    : SignalDecorator(decoratedObject), constantSignal(value) {}

double AddConstantDecorator::generate()
{
    return decoratedObject->generate() + constantSignal.generate();
}
