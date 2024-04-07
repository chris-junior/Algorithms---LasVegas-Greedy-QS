#include "SortIt.h"
#include "Sorted.h"
#include <vector>
#include <random>
#include <any>

int SortIt::N = 0;  // Class Variable

SortIt::SortIt(std::vector<int> values_to_sort, std::vector<int> & values_sorted, std::vector<int> & Heap) {
	unsorted_values = values_to_sort;
	sorted_values = values_sorted;

	heap = Heap;
	

	return;
}


// This is a class Factory, it hides the "new" and reduces the number of parameters seen by the user.
 class Problem * SortIt_Using_Heap(std::vector<int> & values_to_sort)
{
	 // Possible refactoring, make values to sort of std::any instead of ints, and 
	 // recast as needed.
	std::vector<int> Heap;

	Heap = std::vector<int>(values_to_sort);
	std::make_heap(Heap.begin(),Heap.end(), std::greater<>{});

	auto empty = std::vector<int>{};
	return new SortIt(values_to_sort, empty, Heap);
	
}

 

 class Problem* SortIt_Using_Quick(std::vector<std::any>& values_to_sort)
 {
	 // Possible refactoring, make values to sort of std::any instead of ints, and 
	 // recast as needed.
	 
	 return new SortIt(values_to_sort);


 }

 SortIt::SortIt(std::vector<std::any>& AuxList)
 {
	 auxlist = AuxList;
 }

 bool SortIt::trivial() { return unsorted_values.size() < 1; };

bool SortIt::better(class Problem* Reference) { return true; };

bool SortIt::solved() {
	if (sorted_values.size() == SortIt::N) return true;
	if (auxlist.size() == SortIt::N) return true;

	return false;
}

// Helper Function
std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator


std::vector<std::any> split(std::vector<int> list) {
	// This is moved into SortIt as a helper function unaltered.
	// 
	// splits a vector of numbers into {smaller,pivotValue,greaterThanOrEqual}

	if (list.size() == 1)  return std::vector<std::any>{list[1]};
	

	std::uniform_int_distribution<> distr(0, list.size() - 1);
	int location = distr(gen);
	int p = list[location];
	//list.erase(list.begin() + location);
	std::vector<int> smaller = {};
	std::vector<int> greater_or_equal = {};
	int i = 0;
	for (auto el : list)
		if (i++ == location) 
			continue;
		else
			((el < p) ? smaller : greater_or_equal).push_back(el);
	// don't return lists of size zero, or 1. In the case of size 1 return the element.

	std::vector<std::any> result = {};

	if (smaller.size() == 1)
		//result = std::vector<std::any>{ smaller[0] };
		result.push_back(smaller[0]);
	else
		result.push_back(smaller);
		//result = std::vector<std::any>{ smaller };

	if (smaller.size() == 0)
		result = std::vector<std::any>{ p };
	else
		result.push_back(p);

	if (greater_or_equal.size() == 0) return result;

	if (greater_or_equal.size() == 1)
		result.push_back(greater_or_equal[0]);
	else
		result.push_back(greater_or_equal);


	return result;

}
 
class Problem* SortIt::applyRandomAction() {
	// here we will sort using the aux list (before refactoring) 
	// The outer loop will be in the Las Vegas part of the ABC
	
	auto new_result = std::vector<std::any>{};
	 
    for (auto el : auxlist) {
        if (el.type() == typeid(int)) {
            new_result.push_back(el);
        }
        else if (el.type() == typeid(std::vector<int>)) {
            auto r = split(std::any_cast<std::vector<int>>(el));
            for (auto el1 : r)
                new_result.push_back(el1);

        }

    }
	this->auxlist = new_result;
	return this;
	
}

// we will split the unsorted lists into two problems with unsorted lists
std::vector<Problem*> SortIt::make_subproblems() {
	
	// Make two new problems, of each half of the current unsorted parts.
	// if the size of the split vector is 1, create a problem with an empty list to sort with the solution set to the 
	// element.  This is since we consider a trival problem to sort is the empty list.
	auto v = this->unsorted_values;
	if (v.size() == 1)
		return std::vector<Problem*>{new SortIt(std::vector<int>{}, v, v)};
	
	std::size_t const half_size = v.size() / 2;
	std::vector<int> split_lo(v.begin(), v.begin() + half_size);
	std::vector<int> split_hi(v.begin() + half_size, v.end());
	
	return std::vector<Problem*>{SortIt_Using_Heap(split_lo), SortIt_Using_Heap(split_hi)};

};
// Create solution will be called with a unsorted list of a single element and a sorted list.
class aSolution* SortIt::createSolution() 
{   // trival problems are empty lists with a single element in the sorted part.
	// Here we need check if the aux_list is > 1, which means we have sorted using the lasVegas Algorithm
	if (auxlist.size() == SortIt::N) {
		sorted_values = std::vector<int>{};
		for (auto el : auxlist)
			if (el.type() == typeid(int)) 
				sorted_values.push_back(std::any_cast<int>(el));
			  
		return new Sorted({}, sorted_values);
	}
	else
		return new Sorted({}, sorted_values);
};

// This is a helper function.
std::vector<int> merge(std::vector<int> L1, std::vector<int> L2)
{
	std::vector<int> output(L1.size() + L2.size());
	auto it1 = L1.begin();
	auto it2 = L2.begin();
	auto ito = output.begin();

	while (it1 != L1.end())
	{
		auto el1 = *it1++;

		if (it2 != L2.end())
		{
			while (el1 > *it2)
			{
				*ito++ = *it2++;
				if (it2 == L2.end()) break;
			}
		}
		*ito++ = el1;
	}

	while (it2 != L2.end())
	{
		*ito++ = *it2++;  
	}
	return output;
}

class aSolution* SortIt::combineSolutions(std::vector<aSolution*> partialSolutions) { 
	// given two problems with sorted arrays, create a new solution which is the merged in order list.
	if (partialSolutions.size() == 1) return (Sorted*)partialSolutions[0];

	auto S1 = ((Sorted *)partialSolutions[0])->sorted_list;
	auto S2 = ((Sorted *)partialSolutions[1])->sorted_list;

	auto S3 = merge(S1, S2);
	return new Sorted(std::vector<int>{},S3);
}; 

class Problem* SortIt::simplifyProblem() { 
// Not used for this project
	auto empty = std::vector<int>{};
	return new SortIt(std::vector<int>{},empty, empty);
};   

// selectBestAction in this case uses a Heap to select the max.   

static int its = 0;
class Problem* SortIt::applyBestAction() {
	// find the min value
	auto min = heap.front();
	// remove it from the unsorted list (or Heap)
	std::pop_heap(heap.begin(), heap.end(), std::greater<>{});
	heap.pop_back();
	// append it to the sorted list

	sorted_values.push_back(min);

	this->heap = heap;
	this->sorted_values = sorted_values;
	
	//std::cout << "ITS" << its++ << "\n";
	// return the new problem
	return this;
	//return new SortIt(std::vector<int>{}, sorted_values, heap); // the heap are the values
};
