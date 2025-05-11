#pragma once

#include "Signal.h"

/**
 * \author Adrian Skutela
 * \class TriangleSignal
 * \brief Generates a triangle wave signal.
 */
class TriangleSignal : public Signal
{
    long period;
    double amplitude;
    
    long counter;
    long midpoint;
    bool ascending;
public:
    /**
     * \brief Constructs a TriangleSignal instance.
     * \param amplitude The amplitude of the triangle wave.
     * \param period The period of the triangle wave.
     */
    TriangleSignal(double amplitude, long period);

    /**
     * \brief Generates a single sample of the triangle wave.
     * \return A sample value of the triangle wave.
     */
    double generate() override;
};