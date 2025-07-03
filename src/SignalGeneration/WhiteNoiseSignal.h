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

    /**
     * \brief Retrieves the type of the signal.
     * \return A string representing the type of the signal.
     */
    std::string getType() const override;

    /**
     * \brief Serializes the white noise signal to an output stream.
     * \param output The output stream to serialize to.
     */
    void serialize(std::ostream& output) const override;

    /**
     * \brief Deserializes the white noise signal from an input stream.
     * \param input The input stream to deserialize from.
     */
    void deserialize(std::istream& input) override;

    /**
     * \brief A string representing the type of the signal.
     */
    static const std::string type;
};
