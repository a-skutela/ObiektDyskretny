#pragma once

class ObjectSISO
{
public:
    virtual double step(double input) = 0;
    virtual ~ObjectSISO() = default;
};