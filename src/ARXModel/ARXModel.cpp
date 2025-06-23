#include "ARXModel.h"
#include <stdexcept>
#include <numeric>

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
    if (input.eof()) {
        throw std::runtime_error("End of file reached while reading ARXModel from input stream.");
    }
    if (input.fail()) {
        throw std::runtime_error("Error while reading ARXModel from input stream.");
    }
}

double ARXModel::step(double input) 
{
    u.push_front(input);

    double Bu = std::inner_product(B.begin(), B.end(), u.begin() + k, 0.0);
    double Ay = std::inner_product(A.begin(), A.end(), y.begin(), 0.0);
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

void ARXModel::serialize(std::ostream& output) const
{
    output << *this;
}

void ARXModel::deserialize(std::istream& input)
{
    input >> *this;
}

std::string const ARXModel::type = "ARXModel";

std::string ARXModel::getType() const
{
     return ARXModel::type;
}
