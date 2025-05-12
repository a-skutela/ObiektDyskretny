#pragma once

#include "Composite.h"

class FeedbackComposite : public Composite
{
    double y_prev;

public:
    double step(double input);
};
