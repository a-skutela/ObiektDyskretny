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

    /**
     * \brief Retrieves the type of the signal.
     * \return A string representing the type of the signal.
     */
    std::string getType() const override;

    /**
     * \brief Serializes the rectangular signal to an output stream.
     * \param output The output stream to serialize to.
     */
    void serialize(std::ostream& output) const override;

    /**
     * \brief Deserializes the rectangular signal from an input stream.
     * \param input The input stream to deserialize from.
     */
    void deserialize(std::istream& input) override;

    /**
     * \brief A string representing the type of the signal.
     */
    static const std::string type;
};