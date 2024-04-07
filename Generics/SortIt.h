#pragma once
#include "Problem.h"
#include "Sorted.h"
#include <algorithm>
#include <iostream>
#include <any>



class SortIt :
    public Problem
{
	std::vector<int> unsorted_values;
	std::vector<int> sorted_values;
	std::vector<int> heap;
	std::vector<std::any>  auxlist;

	
public:

	SortIt(std::vector<int>  values_to_sort, std::vector<int>& values_sorted, std::vector<int>& heap);
	

	SortIt(std::vector<std::any>& AuxList);
	bool trivial();
	bool solved();
	bool better(class Problem* Reference);
	std::vector<Problem*> make_subproblems();
	class aSolution* createSolution();
	class aSolution* combineSolutions(std::vector<aSolution*> partialSolutions); // in paper this is combine
	class Problem* simplifyProblem();  // in paper this is called refine
	class Problem* applyBestAction();
	class Problem* applyRandomAction();
public:
	static int N;  // Class variable
};


// Class factory like function to create the problem.
class Problem* SortIt_Using_Heap(std::vector<int> & values_to_sort);
class Problem* SortIt_Using_Quick(std::vector<std::any> & values_to_sort);
