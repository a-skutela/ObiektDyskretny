#pragma once

#include <vector>
#include <deque>
#include <random>
#include "../Composition/ConcreteComponent.h"
#include "../ObjectSISO.h"
#include "../Serialization/serialization.h"

/**
 * \author Adrian Skutela
 * \class ARXModel
 * \brief Implements an Auto-Regressive with eXogenous input (ARX) model.
 */
class ARXModel : public ConcreteComponent
{
    std::vector<double> A;
    std::vector<double> B;
    std::deque<double> u;
    std::deque<double> y;
    unsigned int k;

    std::mt19937 generator;
    std::normal_distribution<double> distribution;

public:
    /**
     * \brief Constructs an ARXModel instance.
     * \param A Coefficients of the autoregressive part.
     * \param B Coefficients of the exogenous input part.
     * \param k Delay between input and output.
     * \param stdDev Standard deviation of the noise.
     * \param seed Seed for the random number generator (default is 0).
     */
    ARXModel(std::vector<double> A, std::vector<double> B, unsigned int k, double stdDev, uint_fast32_t seed = 0);

    /**
     * \brief Constructs an ARXModel instance by deserializing from an input stream.
     * \param input The input stream to deserialize from.
     */
    ARXModel(std::istream& input);

    /**
     * \brief Simulates the ARX model for a single input value.
     * \param input The input value.
     * \return The output value of the model.
     */
    double step(double input) override;

    /**
     * \brief Serializes the ARXModel instance to an output stream.
     * \param output The output stream to serialize to.
     */
    void serialize(std::ostream& output) const override;

    /**
     * \brief Deserializes the ARXModel instance from an input stream.
     * \param input The input stream to deserialize from.
     */
    void deserialize(std::istream& input, std::vector<std::shared_ptr<Component>>& gComponents) override;

    /**
     * \brief Compares two ARXModel instances for equality.
     * \param other The other ARXModel instance to compare with.
     * \return True if the models are equal, false otherwise.
     */
    bool operator==(const ARXModel& other) const;

    void setA(std::vector<double> newA);

    void setB(std::vector<double> newB);

    void setK(int newK);

    /**
     * \brief Retrieves the type of the model as a string.
     * \return A string representing the type of the model.
     */
    std::string getType() const override;

    void print(std::ostream& output) const override;

    static const std::string type;

private:
    /**
     * \brief Generates noise based on the normal distribution.
     * \return A random noise value.
     */
    double noise();

    friend std::ostream& operator<<(std::ostream& ost, const ARXModel& arxModel);
    friend std::istream& operator>>(std::istream& input, ARXModel& arxModel);
};
