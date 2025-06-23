#include "AddConstantDecorator.h"

AddConstantDecorator::AddConstantDecorator(std::shared_ptr<Signal> decoratedObject, double value)
    : SignalDecorator(decoratedObject), constantSignal(value) {}

double AddConstantDecorator::generate()
{
    return decoratedObject->generate() + constantSignal.generate();
}

std::string AddConstantDecorator::getType() const
{
    return AddConstantDecorator::type;
}

const std::string AddConstantDecorator::type = "AddConstantDecorator";

void AddConstantDecorator::serializeImpl(std::ostream& output) const
{
    constantSignal.serialize(output);
}

void AddConstantDecorator::deserializeImpl(std::istream& input)
{
    constantSignal.deserialize(input);
}
