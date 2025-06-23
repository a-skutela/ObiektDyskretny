#include "AddSinDecorator.h"

AddSinDecorator::AddSinDecorator(std::shared_ptr<Signal> decoratedObject, double omega, double amplitude)
: SignalDecorator(decoratedObject), sinSignal(omega, amplitude)
{}

double AddSinDecorator::generate()
{
    return decoratedObject->generate() + sinSignal.generate();
}

std::string AddSinDecorator::getType() const
{
    return AddSinDecorator::type;
}

const std::string AddSinDecorator::type = "AddSinDecorator";

void AddSinDecorator::serializeImpl(std::ostream& output) const
{
    sinSignal.serialize(output);
}

void AddSinDecorator::deserializeImpl(std::istream& input)
{
    sinSignal.deserialize(input);
}