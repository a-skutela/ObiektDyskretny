#include "ARXModel.h"
#include <iostream>

ARXModel::ARXModel(std::vector<double> A, std::vector<double> B, unsigned int k, double stdDev, uint_fast32_t seed) 
: A(A), B(B), k(k) 
{
    u = std::deque<double>(B.size() + k, 0);
    y = std::deque<double>(A.size(), 0);

    generator = std::mt19937(seed);
    distribution = std::normal_distribution<double>(0.0, stdDev);
}

ARXModel::ARXModel(std::istream& input)
{
    input >> *this;
}

double ARXModel::step(double input) 
{
    u.push_front(input);

    double Bu = calculateDiscretePolynomial(B, u.begin() + k);;
    double Ay = calculateDiscretePolynomial(A, y.begin());
    double y0 = Bu - Ay + noise();
    
    y.push_front(y0);
    y.pop_back();
    u.pop_back();

    return y0;
}

double ARXModel::noise()
{
    return distribution(generator);
}

bool ARXModel::operator==(const ARXModel& other) const
{
    return A == other.A && 
        B == other.B && 
        k == other.k && 
        generator == other.generator && 
        distribution == other.distribution;
}