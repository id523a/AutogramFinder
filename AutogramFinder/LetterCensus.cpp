#include "LetterCensus.h"

#include <algorithm>

static_assert(std::is_trivially_copyable_v<LetterCensus>);

LetterCensus::LetterCensus() : letterCount{} {
}

LetterCensus::LetterCensus(std::string_view str) : letterCount{} {
	for (char ch : str) {
		if (ch >= 'A' && ch <= 'Z') {
			++letterCount[ch - 'A'];
		} else if (ch >= 'a' && ch <= 'z') {
			++letterCount[ch - 'a'];
		}
	}
}

int& LetterCensus::operator[](char ch) {
	if (ch >= 'A' && ch <= 'Z') {
		return letterCount[ch - 'A'];
	} else if (ch >= 'a' && ch <= 'z') {
		return letterCount[ch - 'a'];
	} else {
		return *(int*)nullptr;
	}
}

int LetterCensus::operator[](char ch) const {
	return (*const_cast<LetterCensus*>(this))[ch];
}

int& LetterCensus::operator[](int idx) {
	return letterCount[idx];
}

int LetterCensus::operator[](int idx) const {
	return (*const_cast<LetterCensus*>(this))[idx];
}

LetterCensus LetterCensus::operator+(const LetterCensus& other) const {
	return LetterCensus(*this) += other;
}

LetterCensus& LetterCensus::operator+=(const LetterCensus& other) {
	for (int i = 0; i < 26; i++) {
		letterCount[i] += other.letterCount[i];
	}
	return *this;
}

LetterCensus LetterCensus::operator-(const LetterCensus& other) const {
	return LetterCensus(*this) -= other;
}

LetterCensus& LetterCensus::operator-=(const LetterCensus& other) {
	for (int i = 0; i < 26; i++) {
		letterCount[i] -= other.letterCount[i];
	}
	return *this;
}

LetterCensus LetterCensus::min(const LetterCensus& other) const {
	return LetterCensus(*this).min_with(other);
}

LetterCensus& LetterCensus::min_with(const LetterCensus& other) {
	for (int i = 0; i < 26; i++) {
		letterCount[i] = std::min(letterCount[i], other.letterCount[i]);
	}
	return *this;
}

LetterCensus LetterCensus::max(const LetterCensus& other) const {
	return LetterCensus(*this).max_with(other);
}

LetterCensus& LetterCensus::max_with(const LetterCensus& other) {
	for (int i = 0; i < 26; i++) {
		letterCount[i] = std::max(letterCount[i], other.letterCount[i]);
	}
	return *this;
}

bool LetterCensus::operator==(const LetterCensus& other) const {
	return std::equal(letterCount, letterCount + 26, other.letterCount);
}
