#include "FeedbackComposite.h"

double FeedbackComposite::step(double input)
{
    double y = input - y_prev;
    for(auto component : components)
    {
        y = component->step(y);
    }
    y_prev = y;
    return y;
}

std::string const FeedbackComposite::type = "FeedbackComposite";

std::string FeedbackComposite::getType() const
{
    return FeedbackComposite::type;
}
