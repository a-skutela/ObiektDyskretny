#include "WhiteNoiseSignal.h"

WhiteNoiseSignal::WhiteNoiseSignal(double stdDev, uint_fast32_t seed)
    : generator(seed), distribution(0.0, stdDev) {}

double WhiteNoiseSignal::generate() 
{
    return distribution(generator);
}