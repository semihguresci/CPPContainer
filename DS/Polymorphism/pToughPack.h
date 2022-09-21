#ifndef TOUGHPACK_H
#define TOUGHPACK_H

#include "pBox.h"

namespace Polymorphism
{
	class ToughPack : public Box
	{
	public:
		using Box::Box;
	protected:
		
		double volume() const override { return 0.85 * m_length * m_width * m_height; }
	};
}
#endif