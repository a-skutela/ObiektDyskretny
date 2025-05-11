#pragma once

/**
 * \author Adrian Skutela
 * \class Signal
 * \brief Abstract base class for signal generation.
 */
class Signal
{
public:
    /**
     * \brief Generates a single sample of the signal.
     * \return A sample value of the signal.
     */
    virtual double generate() = 0;

    /**
     * \brief Virtual destructor for the Signal class.
     */
    virtual ~Signal() = default;
};