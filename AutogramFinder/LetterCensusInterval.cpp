#include "LetterCensusInterval.h"

static_assert(std::is_trivially_copyable_v<LetterCensusInterval>);

LetterCensusInterval::LetterCensusInterval(const LetterCensus& val)
	: lower_bound(val), upper_bound(val) { }

LetterCensusInterval::LetterCensusInterval(const LetterCensus& lb, const LetterCensus& ub)
	: lower_bound(lb), upper_bound(ub) { }

std::pair<int, int> LetterCensusInterval::operator[](char ch) const {
	return std::make_pair(lower_bound[ch], upper_bound[ch]);
}

std::pair<int, int> LetterCensusInterval::operator[](int idx) const {
	return std::make_pair(lower_bound[idx], upper_bound[idx]);
}

LetterCensusInterval& LetterCensusInterval::operator+=(const LetterCensusInterval& other) {
	lower_bound += other.lower_bound;
	upper_bound += other.upper_bound;
	return *this;
}

LetterCensusInterval& LetterCensusInterval::operator-=(const LetterCensusInterval& other) {
	lower_bound -= other.upper_bound;
	upper_bound -= other.lower_bound;
	return *this;
}

LetterCensusInterval& LetterCensusInterval::merge_with(const LetterCensusInterval& other) {
	lower_bound.min_with(other.lower_bound);
	upper_bound.max_with(other.upper_bound);
	return *this;
}

LetterCensusInterval& LetterCensusInterval::intersect_with(const LetterCensusInterval& other) {
	lower_bound.max_with(other.lower_bound);
	upper_bound.min_with(other.upper_bound);
	return *this;
}

LetterCensusInterval LetterCensusInterval::operator+(const LetterCensusInterval& other) const {
	return LetterCensusInterval(*this) += other;
}

LetterCensusInterval LetterCensusInterval::operator-(const LetterCensusInterval& other) const {
	return LetterCensusInterval(*this) -= other;
}

LetterCensusInterval LetterCensusInterval::merge(const LetterCensusInterval& other) const {
	return LetterCensusInterval(*this).merge_with(other);
}

LetterCensusInterval LetterCensusInterval::intersect(const LetterCensusInterval& other) const {
	return LetterCensusInterval(*this).intersect_with(other);
}

bool LetterCensusInterval::operator==(const LetterCensusInterval& other) const {
	return lower_bound == other.lower_bound && upper_bound == other.upper_bound;
}

bool LetterCensusInterval::empty() const {
	for (int i = 0; i < 26; ++i) {
		if (lower_bound[i] > upper_bound[i]) return true;
	}
	return false;
}
