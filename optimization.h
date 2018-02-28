#pragma once

#include "classes.h"
#include <ctime>
#include <algorithm>

// Interface to be defined
vector<char> AddBallon(const Solution& current);

struct CSolutionWithScore {
	Solution Solution;
	int Score;
	bool operator<(const CSolutionWithScore& other) {
		return Score > other.Score;
	}
};

typedef vector<CSolutionWithScore> Population;

const int MaxGenerationSize = 100;
const int GrowingSize = 10;
const int MaxSingleChanges = 3;
const int NumberOfIterations = 100;

void nextGeneration(Population& current)
{
	std::srand(std::time(nullptr));
	for (int k = 0; k < current.size(); k++) {
		Solution newSolution = current[k].Solution;
		for (int i = 0; i < GrowingSize; i++) {
			int numberOfChanges = std::rand() % MaxSingleChanges;
			std::random_shuffle(newSolution.begin(), newSolution.end());
			newSolution._Pop_back_n(numberOfChanges);
			for (int j = 0; j < numberOfChanges; j++) {
				vector<char> ballon = AddBallon(newSolution);
				newSolution.push_back(ballon);
			}
		}
		int score = calc_score(newSolution);
		current.push_back({ newSolution, score });
	}
	std::sort(current.begin(), current.end());
	if (current.size() > MaxGenerationSize) {
		current._Pop_back_n(current.size() - MaxGenerationSize);
	}
}

Solution impove(const Solution& solution)
{
	Population population;
	int score = calc_score(solution);
	population.push_back({ solution, score });
	for (int i = 0; i < NumberOfIterations; i++) {
		printf("Gen %d Best %d\n", i, population[0].Score);
		nextGeneration(population);
	}
	return population[0].Solution;
}
