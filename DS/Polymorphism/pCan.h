#ifndef PCAN_H
#define PCAN_H

#include <Polymorphism/pVessel.h>
#include <numbers>
namespace Polymorphism 
{
    class Can : public Vessel
    {
    public:
        Can(double diameter, double height)
            : m_diameter{ diameter }, m_height{ height } {}

        double volume() const override
        {
            return std::numbers::pi * m_diameter * m_diameter * m_height / 4;
        }

    private:
        double m_diameter, m_height;
    };

}
#endif // !PCAN_H
