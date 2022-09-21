#ifndef FINDER_H
#define FINDER_H

#include <vector>
#include <optional>
namespace FuctionPointerLamda
{
	class Finder
	{
	public:
		double getNumberToSearchFor() const;
		void setNumberToSearchFor(double n);

		std::optional<double> findNearest(const std::vector<double>& values) const;
	private:
		double m_number_to_search_for{};
	};
}
#endif