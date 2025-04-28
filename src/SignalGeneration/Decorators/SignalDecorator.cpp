
#include "SignalDecorator.h"

void SignalDecorator::setDecoratedObject(std::shared_ptr<Signal> decoratedObject)
{
    this->decoratedObject = decoratedObject;
}