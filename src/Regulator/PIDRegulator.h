#pragma once

#include "../ObjectSISO.h"
/**
 * \author Adrian Skutela
 * \class PIDRegulator
 * \brief Class implementing a PID Regulator
 */
class PIDRegulator : public ObjectSISO
{
    double k;
    double Ti;
    double Td;
    double integral;
    double e_prev;
public:
    /**
     * \param k proportional response coefficient
     * \param Ti optional coefficient for integral response. Set to 0.0 to disable integration
     * \param Td optional coefficient for differential response. Set to 0.0 do disable differentiation
     * \brief Constructs an instance of PIDRegulator
     */
    PIDRegulator(double k, double Ti = 0.0, double Td = 0.0);

    /**
     * \brief Calculates output of the regulator for a single input value.
     * \param e input sample
     * \returns output value
     */
    double step(double e) override;
private:
    double proportionalResponse(double e);
    double integralResponse(double e);
    double differentialResponse(double e);
};