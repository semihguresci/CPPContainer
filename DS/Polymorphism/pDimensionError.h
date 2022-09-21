#ifndef PDIMENSION_ERROR_H
#define PDIMENSION_ERROR_H

#include <stdexcept>        
#include <string>           

class DimensionError : public std::out_of_range
{
public:
    explicit DimensionError(double value)
        : std::out_of_range{ "Zero or negative dimension: " + std::to_string(value) }
        , m_value{ value } {}

    double getValue() const noexcept { return m_value; }
private:
    double m_value;
};

#endif