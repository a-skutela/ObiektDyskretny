
#include "SignalDecorator.h"
#include "../ConstantSignal.h"

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