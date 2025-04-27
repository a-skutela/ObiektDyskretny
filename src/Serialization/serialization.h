#pragma once

#include <istream>
#include <ostream>
#include <vector>

class ARXModel;

/**
 * \brief Serializes an ARXModel object to an output stream.
 * \param ost The output stream.
 * \param arxModel The ARXModel object to serialize.
 * \return The output stream.
 */
std::ostream& operator<<(std::ostream& ost, const ARXModel& arxModel);

/**
 * \brief Deserializes an ARXModel object from an input stream.
 * \param input The input stream.
 * \param arxModel The ARXModel object to deserialize into.
 * \return The input stream.
 */
std::istream& operator>>(std::istream& input, ARXModel& arxModel);

/**
 * \brief Serializes a vector to an output stream.
 * \tparam T The type of elements in the vector.
 * \param output The output stream.
 * \param vector The vector to serialize.
 * \return The output stream.
 */
template<typename T>
std::ostream& operator<<(std::ostream& output, const std::vector<T>& vector)
{
    output << vector.size() << " ";
    for (auto& el : vector)
        output << el << " ";
    return output;
}

/**
 * \brief Deserializes a vector from an input stream.
 * \tparam T The type of elements in the vector.
 * \param input The input stream.
 * \param vector The vector to deserialize into.
 * \return The input stream.
 */
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