#pragma once

#include "classes.h"
#include <ctime>
#include <algorithm>
#include <fstream>

// Interface to be defined
vector<char> AddBallon(const Solution& current);

struct CSolutionWithScore {
	Solution Solution;
	int Score;
	bool operator<(const CSolutionWithScore& other) {
		return Score > other.Score;
	}
	void write(ofstream& stream) {
		stream << Solution.size();
		stream << Solution[0].size();
		for (int i = 0; i < Solution.size(); i++) {
			for (int j = 0; j < Solution[0].size(); j++) {
				stream << Solution[i][j];
			}
		}
		stream << Score;
	}
	void read(ifstream& stream) {
		int n, m;
		stream >> n >> m;
		Solution.assign(n, vector<char>(m, 0));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < Solution[0].size(); j++) {
				stream >> Solution[i][j];
			}
		}
		stream >> Score;
	}
};

typedef vector<CSolutionWithScore> Population;

void nextGeneration(Population& current, const int MaxGenerationSize, const int GrowingSize, const int MaxSingleChanges )
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

void dumpPopulation(Population& population, char* filename = "gen.pop")
{
	ofstream outfile;
	outfile.open( filename, ios::out | ios::trunc);
	outfile << population.size();
	for (int i = 0; i < population.size(); i++) {
		population[i].write(outfile);
	}
	outfile.close();
}

void readPopulation(Population& population, char* filename = "gen.pop")
{
	ifstream infile;
	infile.open(filename, ios::in);
	int size;
	infile >> size;
	population.resize(size);
	for (int i = 0; i < size; i++) {
		population[i].read(infile);
	}
	infile.close();
}


Solution improve(const Solution& solution, const int NumberOfIterations = 100, const int MaxGenerationSize = 100, const int GrowingSize = 10, const int MaxSingleChanges = 3 )
{
	Population population;
	int score = calc_score(solution);
	population.push_back({ solution, score });
	for (int i = 0; i < NumberOfIterations; i++) {
		printf("Gen %d Best %d\n", i, population[0].Score);
		nextGeneration(population, MaxGenerationSize, GrowingSize, MaxSingleChanges);
		dumpPopulation(population);
	}
	return population[0].Solution;
}

Solution improveFromDump(const int NumberOfIterations = 100, const int MaxGenerationSize = 100, const int GrowingSize = 10, const int MaxSingleChanges = 3)
{
	Population population;
	readPopulation(population);
	for (int i = 0; i < NumberOfIterations; i++) {
		printf("Gen %d Best %d\n", i, population[0].Score);
		nextGeneration(population, MaxGenerationSize, GrowingSize, MaxSingleChanges);
		dumpPopulation(population);
	}
	return population[0].Solution;
}
