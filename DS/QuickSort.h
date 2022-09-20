#pragma once
#include <iostream>
#include <format>
#include <memory>
#include<string>
#include <sstream>
#include <vector>
#include <optional>

namespace QuickSort
{
	using Words = std::vector<std::shared_ptr<std::string>>;
	void swap(Words& words, size_t first, size_t second);
	void sort(Words& words);
	void sort(Words& words, size_t start, size_t end);
	void extract_words(Words& words, std::string_view& text, std::string_view& separators);
	void show_words(const Words& words);
	size_t max_word_length(const Words& words);
	std::optional<size_t> find_last(std::string_view&, char to_find, std::optional<size_t> start_index = std::nullopt);

	void swap(Words& words, size_t first, size_t second)
	{
		auto temp{ words[first] };
		words[first] = words[second];
		words[second] = temp;
	}

	void sort(Words& words, size_t start, size_t end)
	{
		if (!(start < end))
			return;

		swap(words, start, (start + end) / 2);
		size_t current{ start };
		for (size_t i{ start + 1 }; i <= end; i++)
		{
			if (*words[i] < *words[start])
				swap(words, ++current, i);
		}
		swap(words, start, current);
		if (current > start) 
			sort(words, start, current - 1);
		if (end > current + 1) 
			sort(words, current + 1, end);
	}

	void sort(Words& words)
	{
		if (!words.empty())
			sort(words, 0, words.size() - 1);
	}

	size_t max_word_length(const Words& words)
	{
		size_t max{};
		for (auto& pword : words)
			if (max < pword->length()) max = pword->length();
		return max;
	}

	void show_words(const Words& words)
	{
		const size_t field_width{ max_word_length(words) + 1 };
		const size_t words_per_line{ 8 };
		std::cout << std::format("{:{}}", *words[0], field_width);
		size_t words_in_line{};
		for (size_t i{ 1 }; i < words.size(); ++i)
		{
			if ((*words[i])[0] != (*words[i - 1])[0] || ++words_in_line == words_per_line)
			{
				words_in_line = 0;
				std::cout << std::endl;
			}
			std::cout << std::format("{:{}}", *words[i], field_width);
		}
		std::cout << std::endl;
	}

	void extract_words(Words& words, std::string_view& text, std::string_view& separators)
	{
		size_t start{ text.find_first_not_of(separators) };
		while (start != std::string::npos)
		{
			size_t end = text.find_first_of(separators, start + 1);
			if (end == std::string::npos)
				end = text.length();
			words.push_back(std::make_shared<std::string>(text.substr(start, end - start)));
			start = text.find_first_not_of(separators, end + 1);
		}
	}

	std::optional<size_t> find_last(std::string_view& string, char to_find, std::optional<size_t> start_index)
	{
		if (string.empty())
			return std::nullopt;
				
		size_t index = start_index.value_or(string.size() - 1);
		while (true)
		{
			if (string[index] == to_find) return index;
			if (index == 0) return std::nullopt;
			--index;
		}
	}

	void RunOptional() {

		std::string_view string{ "Growing old is mandatory; growing up is optional." };
		
		const std::optional<size_t> found_a{ find_last(string, 'a') };
		if (found_a)
			std::cout << "Found the last a at index " << *found_a << std::endl;

		const auto found_b{ find_last(string, 'b') };
		if (found_b.has_value())
			std::cout << "Found the last b at index " << found_b.value() << std::endl;
		
		const auto found_early_i{ find_last(string, 'i', 10) };
		if (found_early_i != std::nullopt)
			std::cout << "Found an early i at index " << *found_early_i << std::endl;

	}
	void Run()
	{

		std::cout << std::endl<< "Quick Sort" << std::endl;
		Words words;
		std::string text;

		std::string input("It was the best of times, it was the worst of times, it was the age of wisdom, it was the age of foolishness, it was the epoch of belief, it was the epoch of incredulity, it was the season of Light, it was the season of Darkness, it was the spring of hope, it was the winter of despair, we had everything before us, we had nothing before us, we were all going direct to Heaven, we were all going direct the other way—in short, the period was so far like the \present period, that some of its noisiest authorities insisted on its being received, for good or for evil, in the superlative degree of comparison only.*");

		const auto separators{ " ,.!?\"\n" };
		std::cout << "Enter a string terminated by *:" << std::endl;
		
		std::stringstream myStream(input);
	
		getline(myStream, text, '*');
		std::string_view sv_text(text);
		std::string_view sv_separators(separators);
		extract_words(words, sv_text, sv_separators);
		if (words.empty())
		{
			std::cout << "No words in text." << std::endl;
			return;

		}
		sort(words); 
		show_words(words); 

		RunOptional();
	}
}



