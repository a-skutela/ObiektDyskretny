#pragma once

#include "SignalDecorator.h"
#include "../ConstantSignal.h"

/**
 * @author Adrian Skutela
 * @class AddConstantDecorator
 * @brief A decorator that adds a constant value to a signal.
 */
class AddConstantDecorator : public SignalDecorator
{
    ConstantSignal constantSignal;

public:
    /**
     * @brief Constructs an AddConstantDecorator with a decorated signal and a constant value.
     * @param decoratedObject The signal to be decorated.
     * @param value The constant value to add to the signal.
     */
    AddConstantDecorator(std::shared_ptr<Signal> decoratedObject, double value);

    /**
     * @brief Generates the signal value by adding the constant value to the decorated signal's value.
     * @return The resulting signal value.
     */
    double generate() override;
};
