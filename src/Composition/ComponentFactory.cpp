#include "ComponentFactory.h"
#include "SerialComposite.h"
#include "ParallelComposite.h"
#include "FeedbackComposite.h"
#include "../ARXModel/ARXModel.h"
#include "../Regulator/PIDRegulator.h"

std::shared_ptr<Component> ComponentFactory::createComponent(const std::string& type)
{
    if (type == SerialComposite::type) 
    {
        return std::make_shared<SerialComposite>();
    } 
    else if (type == ParallelComposite::type) 
    {
        return std::make_shared<ParallelComposite>();
    } 
    else if (type == FeedbackComposite::type) 
    {
        return std::make_shared<FeedbackComposite>();
    } 
    else if (type == ARXModel::type) 
    {
        return std::make_shared<ARXModel>(std::vector<double>(), std::vector<double>(), 0, 0.0);
    } 
    else if (type == PIDRegulator::type) 
    {
        return std::make_shared<PIDRegulator>(0.0);
    } 
    else 
    {
        throw std::runtime_error("Unknown component type: " + type);
    }
}
