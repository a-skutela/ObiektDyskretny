#pragma once

#include "Signal.h"

/**
 * \author Adrian Skutela
 * \class ConstantSignal
 * \brief Generates a constant signal with a fixed value.
 */
class ConstantSignal : public Signal
{
    double value;

public:
    /**
     * \brief Constructs a ConstantSignal instance.
     * \param value The constant value of the signal.
     */
    ConstantSignal(double value);

    /**
     * \brief Generates a single sample of the constant signal.
     * \return The constant value of the signal.
     */
    double generate() override;

    /**
     * \brief A constant signal with a value of 0.0.
     */
    static const ConstantSignal zero;
};
