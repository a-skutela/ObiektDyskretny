#include "PIDRegulator.h"

PIDRegulator::PIDRegulator(double k, double Ti, double Td)
: k(k), Ti(Ti), Td(Td)
{
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