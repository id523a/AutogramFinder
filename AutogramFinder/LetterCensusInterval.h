#pragma once

#include "LetterCensus.h"
#include <utility>

class LetterCensusInterval {
public:
	LetterCensus lower_bound;
	LetterCensus upper_bound;
	LetterCensusInterval() = default;
	LetterCensusInterval(const LetterCensus& val);
	LetterCensusInterval(const LetterCensus& lb, const LetterCensus& ub);

	std::pair<int, int> operator [](char ch) const;
	std::pair<int, int> operator [](int idx) const;

	LetterCensusInterval& operator +=(const LetterCensusInterval& other);
	LetterCensusInterval& operator -=(const LetterCensusInterval& other);
	LetterCensusInterval& merge_with(const LetterCensusInterval& other);
	LetterCensusInterval& intersect_with(const LetterCensusInterval& other);

	LetterCensusInterval operator +(const LetterCensusInterval& other) const;
	LetterCensusInterval operator -(const LetterCensusInterval& other) const;
	LetterCensusInterval merge(const LetterCensusInterval& other) const;
	LetterCensusInterval intersect(const LetterCensusInterval& other) const;

	bool operator==(const LetterCensusInterval& other) const;
	inline bool operator!=(const LetterCensusInterval& other) const { return !(*this == other); }

	bool empty() const;
};