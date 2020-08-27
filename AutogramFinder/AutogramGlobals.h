#pragma once

#include <vector>
#include <string>

#include "LetterCensus.h"
#include "LetterCensusInterval.h"

namespace AutogramGlobals {
	const std::string& getNumberName(int N);
	const LetterCensus& getLetterCensus(int N);
	LetterCensusInterval getLetterCensusBounds(int LB, int UB);
};