#pragma once

#include "SignalDecorator.h"

/**
 * \author Adrian Skutela
 * \class ClampDecorator
 * \brief Decorator that clamps the amplitude of a signal to a specified range.
 */
class ClampDecorator : public SignalDecorator
{
    double minValue;
    double maxValue;

public:
    /**
     * \brief Constructs a ClampDecorator instance.
     * \param decoratedObject The signal to be decorated.
     * \param minValue The minimum allowed amplitude.
     * \param maxAmplitude The maximum allowed amplitude.
     */
    ClampDecorator(std::shared_ptr<Signal> decoratedObject, double minValue, double maxValue);

    /**
     * \brief Generates a single sample of the decorated signal.
     * \return A sample value of the decorated signal, clamped to the specified range.
     */
    double generate() override;
};
