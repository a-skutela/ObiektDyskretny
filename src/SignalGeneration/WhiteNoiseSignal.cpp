#include "WhiteNoiseSignal.h"

WhiteNoiseSignal::WhiteNoiseSignal(double stdDev, uint_fast32_t seed)
    : generator(seed), distribution(0.0, stdDev) {}

double WhiteNoiseSignal::generate() 
{
    return distribution(generator);
}

std::string WhiteNoiseSignal::getType() const
{
    return WhiteNoiseSignal::type;
}

void WhiteNoiseSignal::serialize(std::ostream& output) const
{
    output << " " << distribution.stddev() << " " << generator.default_seed << "\n";
}

void WhiteNoiseSignal::deserialize(std::istream& input)
{
    double stdDev;
    uint_fast32_t seed;
    input >> stdDev >> seed;
    distribution = std::normal_distribution<double>(0.0, stdDev);
    generator.seed(seed);
}

std::string const WhiteNoiseSignal::type = "WhiteNoiseSignal";

