#include "SignalFactory.h"
#include "SinSignal.h"
#include "RectSignal.h"
#include "TriangleSignal.h"
#include "WhiteNoiseSignal.h"
#include "ConstantSignal.h"
#include "Decorators/AddConstantDecorator.h"
#include "Decorators/AddRectDecorator.h"
#include "Decorators/AddTriangleDecorator.h"
#include "Decorators/AddSinDecorator.h"
#include "Decorators/AddWhiteNoiseDecorator.h"
#include "Decorators/ClampDecorator.h"

std::shared_ptr<Signal> SignalFactory::createSignal(const std::string& type)
{
    if (type == SinSignal::type)
    {
        return std::make_shared<SinSignal>(0.0, 1.0);
    }
    else if (type == RectSignal::type)
    {
        return std::make_shared<RectSignal>(1.0, 1000, 0.5);
    }
    else if (type == TriangleSignal::type)
    {
        return std::make_shared<TriangleSignal>(1.0, 1000);
    }
    else if (type == WhiteNoiseSignal::type)
    {
        return std::make_shared<WhiteNoiseSignal>(1.0);
    }
    else if (type == ConstantSignal::type)
    {
        return std::make_shared<ConstantSignal>(0.0);
    }
    else if (type == AddConstantDecorator::type)
    {
        return std::make_shared<AddConstantDecorator>(std::make_shared<ConstantSignal>(0.0), 1.0);
    }
    else if (type == AddRectDecorator::type)
    {
        return std::make_shared<AddRectDecorator>(std::make_shared<ConstantSignal>(0.0), 1.0, 1000, 0.5);
    }
    else if (type == AddTriangleDecorator::type)
    {
        return std::make_shared<AddTriangleDecorator>(std::make_shared<ConstantSignal>(0.0), 1.0, 1000);
    }
    else if (type == AddSinDecorator::type)
    {
        return std::make_shared<AddSinDecorator>(std::make_shared<ConstantSignal>(0.0), 1.0, 1.0);
    }
    else if (type == AddWhiteNoiseDecorator::type)
    {
        return std::make_shared<AddWhiteNoiseDecorator>(std::make_shared<ConstantSignal>(0.0), 1.0);
    }
    else if (type == ClampDecorator::type)
    {
        return std::make_shared<ClampDecorator>(std::make_shared<ConstantSignal>(0.0), 0.0, 1.0);
    }
    else
    {
        return nullptr;
    }
}
