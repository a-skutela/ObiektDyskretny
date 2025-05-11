#pragma once

#include "Signal.h"

/**
 * \author Adrian Skutela
 * \class RectSignal
 * \brief Generates a rectangular wave signal.
 */
class RectSignal : public Signal
{
    long period;
    double fillFactor;
    double amplitude;
    
    long counter;
    double levelSwitch;
public:
    /**
     * \brief Constructs a RectSignal instance.
     * \param amplitude The amplitude of the rectangular wave.
     * \param period The period of the rectangular wave.
     * \param fillFactor The fill factor (duty cycle) of the rectangular wave.
     */
    RectSignal(double amplitude, long period, double fillFactor);
    
    /**
     * \brief Generates a single sample of the rectangular wave.
     * \return A sample value of the rectangular wave.
     */
    double generate() override;
};