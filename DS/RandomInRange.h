#pragma once
#include <iostream>
#include <format>
#include<string>
#include <random>

namespace RandomInRange 
{
	template < typename T, auto lower, auto upper>
	bool is_in_range(const T& value)
	{
		return (value <= upper) && (value >= lower);
	}

	template <typename T, T lowerlimit, T upperLimit>
	T getRandomNum() {
		std::random_device r;
		std::default_random_engine e1(r());
		std::uniform_int_distribution<T> ud(lowerlimit, upperLimit);
		return  ud(e1);
	}
	
	void Run() {
		std::random_device r;
		std::default_random_engine e1(r());
		std::uniform_int_distribution<int> ud(0, 200);
		int randnum = ud(e1);
		std::cout << std::endl << std::format("{} is in range ", randnum) << std::boolalpha << is_in_range<int, 100, 200>(randnum) << std::endl;
	}
}
