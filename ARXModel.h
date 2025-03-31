#pragma once

#include "ObjectSISO.h"
#include <vector>
#include <deque>
#include <numeric>

class ARXModel : ObjectSISO
{
    std::vector<double> A;
    std::vector<double> B;
    std::deque<double> u;
    std::deque<double> y;
    unsigned int k;

public:
    ARXModel(std::vector<double> A, std::vector<double> B, unsigned int k, double stdDev);

    double Step(double input);

private:
    double Noise();
};