#pragma once

#include "../ObjectSISO.h"
#include "../Composition/ConcreteComponent.h"
#include <string>

/**
 * \author Adrian Skutela
 * \class PIDRegulator
 * \brief Implements a Proportional-Integral-Derivative (PID) regulator.
 */
class PIDRegulator : public ConcreteComponent
{
    double k;
    double Ti;
    double Td;
    double integral;
    double e_prev;
public:
    /**
     * \brief Constructs a PIDRegulator instance.
     * \param k Proportional response coefficient.
     * \param Ti Optional coefficient for integral response. Set to 0.0 to disable integration.
     * \param Td Optional coefficient for differential response. Set to 0.0 to disable differentiation.
     */
    PIDRegulator(double k, double Ti = 0.0, double Td = 0.0);

    /**
     * \brief Calculates the output of the regulator for a single input value.
     * \param e The input error value.
     * \return The output value of the regulator.
     */
    double step(double e) override;

    /**
     * \brief Sets the proportional response coefficient.
     * \param k The new proportional response coefficient. Must be non-negative.
     * \throws std::invalid_argument if k is negative.
     */
    void setK(double k);

    /**
     * \brief Sets the integral response coefficient.
     * \param Ti The new integral response coefficient. Must be non-negative.
     * \throws std::invalid_argument if Ti is negative.
     */
    void setTi(double Ti);

    /**
     * \brief Sets the differential response coefficient.
     * \param Td The new differential response coefficient. Must be non-negative.
     * \throws std::invalid_argument if Td is negative.
     */
    void setTd(double Td);

    /**
     * \brief Prints the ARX model details to an output stream.
     * \param output The output stream to print to.
     */
    void print(std::ostream& output) const override;

    /**
     * \brief Serializes the PIDRegulator instance to an output stream.
     * \param output The output stream to serialize to.
     */
    void serialize(std::ostream& output) const override;

    /**
     * \brief Deserializes the PIDRegulator instance from an input stream.
     * \param input The input stream to deserialize from.
     */
    void deserialize(std::istream& input, std::vector<std::shared_ptr<Component>>& gComponents) override;

    /**
     * \brief Retrieves the type of the regulator as a string.
     * \return A string representing the type of the regulator.
     */
    std::string getType() const override;

    /**
     * \brief A string representing the type of the component.
     */
    static const std::string type;

private:
    double proportionalResponse(double e);
    double integralResponse(double e);
    double differentialResponse(double e);

    /**
     * \brief Validates that a parameter is non-negative.
     * \param value The value to validate.
     * \param name The name of the parameter (used in the exception message).
     * \throws std::invalid_argument if the value is negative.
     */
    void validateNonNegative(double value, const std::string& name);
};