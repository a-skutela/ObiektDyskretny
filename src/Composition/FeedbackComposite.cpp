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

void FeedbackComposite::serialize(std::ostream& output) const
{
    output << y_prev << " ";
    serializeImpl(output);
}

void FeedbackComposite::deserialize(std::istream& input, std::vector<std::shared_ptr<Component>>& components)
{
    input >> y_prev;
    if (input.fail()) {
        throw std::runtime_error("Error while reading FeedbackComposite from input stream.");
    }
    deserializeImpl(input, components);
}
