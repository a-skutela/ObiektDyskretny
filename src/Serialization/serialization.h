#pragma once

#include <iostream>
#include <vector>

class ARXModel;

std::ostream& operator<<(std::ostream& ost, const ARXModel& arxModel);
std::istream& operator>>(std::istream& input, ARXModel& arxModel);

template<typename T>
std::ostream& operator<<(std::ostream& output, const std::vector<T>& vector)
{
    output << vector.size() << " ";
    for (auto& el : vector)
        output << el << " ";
    return output;
}

template<typename T>
std::istream& operator>>(std::istream& input, std::vector<T>& vector)
{
    size_t size;
    input >> size;

    vector.clear();
    vector.reserve(size);
    for (size_t i = 0; i < size; i++)
    {
        double el;
        input >> el;
        vector.push_back(el);
    }
    return input;
}