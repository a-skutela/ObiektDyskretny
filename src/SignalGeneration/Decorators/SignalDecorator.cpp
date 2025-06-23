#include "SignalDecorator.h"
#include "../ConstantSignal.h"
#include "../SignalFactory.h"

SignalDecorator::SignalDecorator(std::shared_ptr<Signal> decoratedObject)
{
    setDecoratedObject(decoratedObject);
}

void SignalDecorator::setDecoratedObject(std::shared_ptr<Signal> decoratedObject)
{
    if (decoratedObject == nullptr)
    {
        decoratedObject = std::make_shared<ConstantSignal>(0.0);
    }
    
    this->decoratedObject = decoratedObject;
}

void SignalDecorator::serialize(std::ostream& output) const
{
    serializeImpl(output);

    output << decoratedObject->getType() << " ";
    decoratedObject->serialize(output);
    output << std::endl;
}

void SignalDecorator::deserialize(std::istream& input)
{
    deserializeImpl(input);

    std::string type;
    input >> type;

    if (input.fail())
    {
        throw std::runtime_error("Error reading signal type from input stream.");
    }

    std::shared_ptr<Signal> signal = SignalFactory::createSignal(type);

    if (signal)
    {
        signal->deserialize(input);
        decoratedObject = signal;
    }
    else
    {
        throw std::runtime_error("Type mismatch during deserialization.");
    }
}