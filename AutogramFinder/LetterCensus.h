#pragma once

#include <string_view>

class LetterCensus {
private:
	int letterCount[26];
public:
	LetterCensus();
	LetterCensus(std::string_view str);
	int& operator [](char ch);
	int operator [](char ch) const;
	int& operator [](int idx);
	int operator [](int idx) const;

	LetterCensus operator +(const LetterCensus& other) const;
	LetterCensus& operator +=(const LetterCensus& other);
	LetterCensus operator -(const LetterCensus& other) const;
	LetterCensus& operator -=(const LetterCensus& other);

	LetterCensus min(const LetterCensus& other) const;
	LetterCensus& min_with(const LetterCensus& other);
	LetterCensus max(const LetterCensus& other) const;
	LetterCensus& max_with(const LetterCensus& other);

	bool operator==(const LetterCensus& other) const;
	inline bool operator!=(const LetterCensus& other) const { return !(*this == other); }
};