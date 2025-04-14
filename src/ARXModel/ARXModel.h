#pragma once

#include <vector>
#include <deque>
#include <numeric>
#include <random>
#include <iostream>
#include "../ObjectSISO.h"
#include "../Serialization/serialization.h"

class ARXModel : public ObjectSISO
{
    std::vector<double> A;
    std::vector<double> B;
    std::deque<double> u;
    std::deque<double> y;
    unsigned int k;

    std::mt19937 generator;
    std::normal_distribution<double> distribution;

public:
    ARXModel(std::vector<double> A, std::vector<double> B, unsigned int k, double stdDev, uint_fast32_t seed = 0);
    ARXModel(std::istream& input);

    double step(double input) override;
    bool operator==(const ARXModel& other) const;

private:
    double noise();

    template<typename InputIterator>
    double calculateDiscretePolynomial(std::vector<double> polynomial, InputIterator inputStart);

    friend std::ostream& operator<<(std::ostream& ost, const ARXModel& arxModel);
    friend std::istream& operator>>(std::istream& input, ARXModel& arxModel);
};

template<typename InputIterator>
double ARXModel::calculateDiscretePolynomial(std::vector<double> polynomial, InputIterator inputStart)
{
    return std::inner_product(polynomial.begin(), polynomial.end(), inputStart, 0.0);
}
