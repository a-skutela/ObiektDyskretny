
#include "SignalDecorator.h"
#include "../SinSignal.h"

class AddSinDecorator : public SignalDecorator
{
    SinSignal sinSignal;
public:
    AddSinDecorator(std::shared_ptr<Signal> decoratedObject, double omega, double amplitude);

    double generate(int n) override;
};