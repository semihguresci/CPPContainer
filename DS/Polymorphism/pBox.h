#ifndef PBOX_H
#define PBOX_H
#include <Polymorphism/pVessel.h>
#include <Polymorphism/pDimensionError.h>

namespace Polymorphism 
{
	class Box : public Vessel
	{
	public:
		Box(double l, double w, double h) : m_length{ l }, m_width{ w }, m_height{ h } 
		{
			if (l <= 0.0 || w <= 0.0 || h <= 0.0)
				throw DimensionError{ std::min({l, w, h}) };
		}

		double volume() const override 
		{ 
			return m_length * m_width * m_height; 
		}

	protected:   
		double m_length, m_width, m_height;
	};

}

#endif // !PBOX_H
