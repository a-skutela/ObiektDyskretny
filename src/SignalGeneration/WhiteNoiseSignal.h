#pragma once

#include <random>
#include "Signal.h"

/**
 * \author Adrian Skutela
 * \class WhiteNoiseSignal
 * \brief Generates white noise based on a normal distribution.
 */
class WhiteNoiseSignal : public Signal
{
    std::mt19937 generator;
    std::normal_distribution<double> distribution;

public:
    /**
     * \brief Constructs a WhiteNoiseSignal instance.
     * \param stdDev Standard deviation of the noise.
     * \param seed Seed for the random number generator (default is 0).
     */
    WhiteNoiseSignal(double stdDev, uint_fast32_t seed = 0);

    /**
     * \brief Generates a single sample of white noise.
     * \return A random noise value.
     */
    double generate() override;
};
