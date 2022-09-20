#pragma once
#include <iostream>
#include <string>


namespace RomanTest {

unsigned int from_roman(char c)
{
	switch (c)
	{
	case 'I': return 1; case 'V': return 5; case 'X': return 10;
	case 'L': return 50; case 'C': return 100; case 'D': return 500;
	case 'M': return 1000; default: return 0;
	}
}
unsigned int from_roman(std::string_view roman)
{
	unsigned int result{};
	for (size_t i{}, n{ roman.length() }; i < n; ++i)
	{
		const auto j{ from_roman(roman[i]) }; // Integer value of the i'th roman digit
		// Look at the next digit (if there is one) to know whether to add or subtract j
		if (i + 1 == n || j >= from_roman(roman[i + 1])) result += j; else result -= j;
	}
	return result;
}
std::string to_roman(unsigned int i)
{
	if (i > 3999) return {}; // 3999, or MMMCMXCIX, is the largest standard Roman numeral
	static const std::string ms[]{ "","M","MM","MMM" };
	static const std::string cds[]{ "","C","CC","CCC","CD","D","DC","DCC","DCCC","CM" };
	static const std::string xls[]{ "","X","XX","XXX","XL","L","LX","LXX","LXXX","XC" };
	static const std::string ivs[]{ "","I","II","III","IV","V","VI","VII","VIII","IX" };
	return ms[i / 1000] + cds[(i % 1000) / 100] + xls[(i % 100) / 10] + ivs[i % 10];
}

	void Run()
	{
		std::cout << "1234 in Roman numerals is " << to_roman(1234) << std::endl;
		std::cout << "MMXX in Arabic numerals is " << from_roman("MMXXII") << std::endl;
	}
}
