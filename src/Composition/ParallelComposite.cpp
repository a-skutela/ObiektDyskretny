#include "ParallelComposite.h"
#include <numeric>
#include <algorithm>

double ParallelComposite::step(double input)
{
    std::vector<double> outputs(components.size());
    std::transform(
        components.begin(), 
        components.end(), 
        outputs.begin(), 
        [input](std::shared_ptr<Component> component){
            return component->step(input);
        });
    return std::accumulate(outputs.begin(), outputs.end(), 0.0);
}

std::string const ParallelComposite::type = "ParallelComposite";

std::string ParallelComposite::getType() const
{
    return ParallelComposite::type;
}

void ParallelComposite::serialize(std::ostream& output) const
{
    serializeImpl(output);
}

void ParallelComposite::deserialize(std::istream& input, std::vector<std::shared_ptr<Component>>& gComponents)
{
    deserializeImpl(input, components);
}
