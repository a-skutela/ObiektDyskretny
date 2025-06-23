#include "AddWhiteNoiseDecorator.h"

AddWhiteNoiseDecorator::AddWhiteNoiseDecorator(std::shared_ptr<Signal> decoratedObject, double amplitude)
    : SignalDecorator(decoratedObject), whiteNoiseSignal(amplitude)
{
}

double AddWhiteNoiseDecorator::generate()
{
    return decoratedObject->generate() + whiteNoiseSignal.generate();
}

const std::string AddWhiteNoiseDecorator::type = "AddWhiteNoiseDecorator";

std::string AddWhiteNoiseDecorator::getType() const
{
    return AddWhiteNoiseDecorator::type;
}

void AddWhiteNoiseDecorator::serializeImpl(std::ostream& output) const
{
    whiteNoiseSignal.serialize(output);
}

void AddWhiteNoiseDecorator::deserializeImpl(std::istream& input)
{
    whiteNoiseSignal.deserialize(input);
}
