// AutogramFinder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>

#include "AutogramGlobals.h"

bool reduce_solution(LetterCensusInterval& soln, const LetterCensus& template_string) {
	// Iterate until a fixed point is found
	bool changeMade = true;
	while (changeMade) {
		LetterCensusInterval reduced_solution(template_string);
		for (int i = 0; i < 26; ++i) {
			if (soln.lower_bound[i] > soln.upper_bound[i]) {
				// If the interval is empty, give up
				return false;
			}
			// Compute the bounds on the census of letters required to spell the number of times the letter [i] appears
			reduced_solution += AutogramGlobals::getLetterCensusBounds(soln.lower_bound[i], soln.upper_bound[i]);
		}
		// intersect old solution with new solution
		changeMade = false;
		for (int i = 0; i < 26; ++i) {
			if (reduced_solution.lower_bound[i] > soln.lower_bound[i]) {
				soln.lower_bound[i] = reduced_solution.lower_bound[i];
				changeMade = true;
			}
			if (reduced_solution.upper_bound[i] < soln.upper_bound[i]) {
				soln.upper_bound[i] = reduced_solution.upper_bound[i];
				changeMade = true;
			}
		}
	}
	return true;
}

LetterCensus NO_SOLUTION;

uint32_t counter = 0;

LetterCensus search(LetterCensusInterval lci, const LetterCensus& template_string) {
	if (!reduce_solution(lci, template_string)) return NO_SOLUTION;
	if (++counter > 500000) {
		counter = 0;
		std::cout << "\nLB: ";
		for (int i = 0; i < 26; ++i) {
			std::cout << char('A' + i);
			std::cout.width(3);
			std::cout << std::left << lci.lower_bound[i];
		}
		std::cout << '\n';
		std::cout << "UB: ";
		for (int i = 0; i < 26; ++i) {
			std::cout << ' ';
			std::cout.width(3);
			std::cout << std::left << lci.upper_bound[i];
		}
		std::cout << std::endl;
	}
	// Find variable (letter) with fewest values (possible letter counts) other than 1.
	// If all variables have 1 possible value, it's the solution!
	int mrv = -1;
	int minCount = INT_MAX;
	for (int i = 0; i < 26; ++i) {
		int range = lci.upper_bound[i] - lci.lower_bound[i];
		if (range > 0 && range < minCount) {
			minCount = range;
			mrv = i;
		}
	}
	if (mrv == -1) {
		return lci.lower_bound;
	}
	int minVal = lci.lower_bound[mrv];
	int maxVal = lci.upper_bound[mrv];
	for (int testVal = minVal; testVal <= maxVal; ++testVal) {
		lci.lower_bound[mrv] = testVal;
		lci.upper_bound[mrv] = testVal;
		// Recursive search. Pass on solution if it is valid.
		LetterCensus soln = search(lci, template_string);
		if (soln['a'] != -1) return soln;
	}
	return NO_SOLUTION;
}

int main()
{
	NO_SOLUTION['a'] = -1;
	LetterCensusInterval root;
	for (int i = 0; i < 26; ++i) {
		root.lower_bound[i] = 0;
		root.upper_bound[i] = 9999;
	}
	
	LetterCensus template_string("This sentence has abcdefghijklmnopqrstuvwxy and z.");
	reduce_solution(root, template_string);
	LetterCensus result = search(root, template_string);
	for (char i = 'a'; i <= 'z'; ++i) {
		std::cout << i << ": " << result[i] << '\n';
	}
	return 0;
}
