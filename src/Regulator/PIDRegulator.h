#pragma once

#include "../ObjectSISO.h"

class PIDRegulator : public ObjectSISO
{
    double k;
    double Ti;
    double Td;
    double integral;
    double e_prev;
public:
    PIDRegulator(double k, double Ti = 0.0, double Td = 0.0);

    double step(double e) override;
private:
    double proportionalResponse(double e);
    double integralResponse(double e);
    double differentialResponse(double e);
};