
#include <memory>
#include "../Signal.h"

class SignalDecorator : public Signal
{
protected:
    std::shared_ptr<Signal> decoratedObject;

public:
    SignalDecorator(std::shared_ptr<Signal> decoratedObject);
    void setDecoratedObject(std::shared_ptr<Signal> decoratedObject);
};