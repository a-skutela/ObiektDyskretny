#pragma once

#include "SignalDecorator.h"
#include "../WhiteNoiseSignal.h"

/**
 * \author Adrian Skutela
 * \class AddWhiteNoiseDecorator
 * \brief Decorator that adds white noise to an existing signal.
 */
class AddWhiteNoiseDecorator : public SignalDecorator
{
    WhiteNoiseSignal whiteNoiseSignal;

public:
    /**
     * \brief Constructs an AddWhiteNoiseDecorator instance.
     * \param decoratedObject The signal to be decorated.
     * \param amplitude The amplitude of the white noise.
     */
    AddWhiteNoiseDecorator(std::shared_ptr<Signal> decoratedObject, double amplitude);

    /**
     * \brief Generates a single sample of the decorated signal.
     * \return A sample value of the decorated signal.
     */
    double generate() override;
};
