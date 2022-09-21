#ifndef CARTON_H
#define CARTON_H
#include <algorithm>    
#include <string>
#include <string_view>
#include "pBox.h"
namespace Polymorphism
{
    class Carton : public Box
    {
    public:
        Carton(double l, double w, double h, std::string_view mat = "cardboard")
            : Box{ l, w, h }, m_material{ mat }
        {}

        double volume() const override
        {
            const double volume{ (m_length - 0.5) * (m_width - 0.5) * (m_height - 0.5) };
            return std::max(volume, 0.0);     
        }
    private:
        std::string m_material;
    };
}

#endif