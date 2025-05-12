#pragma once

#include "Composite.h"

class ParallelComposite : public Composite
{
public:
    double step(double input);
};