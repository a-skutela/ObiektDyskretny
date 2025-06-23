#include "PIDRegulator.h"
#include <stdexcept>

PIDRegulator::PIDRegulator(double k, double Ti, double Td)
: k(k), Ti(Ti), Td(Td)
{
    validateNonNegative(k, "k");
    validateNonNegative(Ti, "Ti");
    validateNonNegative(Td, "Td");

    integral = 0.0;
    e_prev = 0.0;
}

double PIDRegulator::step(double e)
{
    return proportionalResponse(e) + integralResponse(e) + differentialResponse(e);
}

double PIDRegulator::proportionalResponse(double e)
{
    return k * e;
}

double PIDRegulator::integralResponse(double e)
{
    if (Ti != 0)
    {
        integral += e;
        return 1.0 / Ti * integral;
    }
    else
    {
        return 0.0;
    }
}

double PIDRegulator::differentialResponse(double e)
{
    double response = Td * (e - e_prev);
    e_prev = e;
    return response;
}

void PIDRegulator::setK(double k)
{
    validateNonNegative(k, "k");
    this->k = k;
}

void PIDRegulator::setTi(double Ti)
{
    validateNonNegative(Ti, "Ti");
    this->Ti = Ti;
}

void PIDRegulator::setTd(double Td)
{
    validateNonNegative(Td, "Td");
    this->Td = Td;
}

void PIDRegulator::validateNonNegative(double value, const std::string& name)
{
    if (value < 0)
    {
        throw std::invalid_argument(name + " must be non-negative.");
    }
}

const std::string PIDRegulator::type = "PIDRegulator";

void PIDRegulator::serialize(std::ostream& output) const
{
    output << k << " " << Ti << " " << Td << " " << integral << " " << e_prev << std::endl;
}

void PIDRegulator::deserialize(std::istream& input)
{
    input >> k >> Ti >> Td >> integral >> e_prev;
    if (input.fail())
    {
        throw std::runtime_error("Error while deserializing PIDRegulator from input stream.");
    }
}

std::string PIDRegulator::getType() const
{
    return PIDRegulator::type;
}