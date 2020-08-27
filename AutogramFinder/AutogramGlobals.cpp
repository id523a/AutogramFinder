#include "AutogramGlobals.h"

#include <cassert>

namespace AutogramGlobals {
	const char* tensWords[] = {
		"zero", "ten", "twenty", "thirty", "forty",
		"fifty", "sixty", "seventy", "eighty", "ninety"
	};
	std::vector<std::string> numberNameCache = {
		"zero", "one", "two", "three", "four", 
		"five", "six", "seven", "eight", "nine",
		"ten", "eleven", "twelve", "thirteen", "fourteen",
		"fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
	};
	std::vector<LetterCensus> letterCensusCache;
	std::vector<std::vector<LetterCensusInterval>> letterCensusTree;
	std::string computeNumberName(int N) {
		// Assume number is within range.
		assert(N >= 20 && N < 20000);
		std::string result;
		int thousands = N / 1000;
		int hundreds = (N / 100) % 10;
		int sub_hundreds = N % 100;
		if (thousands > 0) {
			result.append(numberNameCache[thousands]);
			result.append(" thousand");
		}
		if (hundreds > 0) {
			if (thousands > 0) {
				result.append(" ");
			}
			result.append(numberNameCache[hundreds]);
			result.append(" hundred");
		}
		if ((thousands > 0 || hundreds > 0) && sub_hundreds > 0) {
			result.append(" and ");
		}
		if (sub_hundreds >= 20) {
			result.append(tensWords[sub_hundreds / 10]);
			int ones = sub_hundreds % 10;
			if (ones > 0) {
				result.append(" ");
				result.append(numberNameCache[ones]);
			}
		} else {
			result.append(numberNameCache[sub_hundreds]);
		}

		return result;
	}
	const std::string& getNumberName(int N) {
		assert(N >= 0);
		numberNameCache.reserve(N + 1);
		while (numberNameCache.size() <= (size_t)N) {
			numberNameCache.push_back(computeNumberName(numberNameCache.size()));
		}
		return numberNameCache[N];
	}
	const LetterCensus& getLetterCensus(int N) {
		assert(N >= 0);
		getNumberName(N);
		letterCensusCache.reserve(N + 1);
		for (size_t i = letterCensusCache.size(); i <= (size_t)N; ++i) {
			LetterCensus census(numberNameCache[i]);
			// Include the plural 's' in the census when required
			if (i != 1) census['s'] += 1;
			letterCensusCache.push_back(census);
		}
		return letterCensusCache[N];
	}
	void updateSegmentTreeLevel(const std::vector<LetterCensusInterval>& child, std::vector<LetterCensusInterval>& parent) {
		size_t newSize = child.size() / 2;
		parent.reserve(newSize);
		for (size_t i = parent.size(); i < newSize; ++i) {
			parent.emplace_back(child[2 * i]);
			parent[i].merge_with(child[2 * i + 1]);
		}
	}
	void updateSegmentTree() {
		if (letterCensusTree.size() == 0) {
			letterCensusTree.emplace_back();
		}
		auto& treeRoot = letterCensusTree[0];
		for (size_t i = treeRoot.size(); i < letterCensusCache.size(); ++i) {
			treeRoot.emplace_back(letterCensusCache[i]);
		}
		size_t layerSize = treeRoot.size() / 2;
		size_t layerIdx = 1;
		while (layerSize > 0) {
			while (layerIdx >= letterCensusTree.size()) {
				letterCensusTree.emplace_back();
			}
			updateSegmentTreeLevel(letterCensusTree[layerIdx - 1], letterCensusTree[layerIdx]);
			++layerIdx;
			layerSize /= 2;
		}
	}
	LetterCensus temp;
	LetterCensusInterval getLetterCensusBounds(int LB, int UB) {
		assert(LB >= 0);
		assert(UB >= LB);
		LetterCensusInterval result(getLetterCensus(UB));
		updateSegmentTree();
		// Look up value in segment tree
		size_t a = LB;
		size_t b = UB + 1;
		size_t treeLevel = 0;
		while (a < b) {
			assert(treeLevel < letterCensusTree.size());
			if (a & 1) {
				result.merge_with(letterCensusTree[treeLevel][a]);
			}
			a = (a + 1) / 2;
			if (b & 1) {
				result.merge_with(letterCensusTree[treeLevel][b - 1]);
			}
			b = b / 2;
			++treeLevel;
		}
		return result;
	}
};