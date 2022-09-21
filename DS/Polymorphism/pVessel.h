#ifndef VESSEL_H
#define VESSEL_H
namespace Polymorphism
{
	class Vessel {
	public:
		virtual ~Vessel() = default;
		virtual double volume() const = 0;
	};
}
#endif // !VESSEL_H
