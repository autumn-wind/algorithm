#include<chrono>
#include<algorithm>
#include<iostream>

#include<time.h>

#include"sort_algo.h"

const String_Function_Map&
Sort_Registration::algos() {
    static String_Function_Map sort_algorithms {
	    {"Selection", Selection::sort},
	    {"Insertion", Insertion::sort}, 
	    {"STL", STL::sort}};
    return sort_algorithms;
}

void 
Selection::sort(std::vector<Comparable> &a) {
    for (int i = 0; i < a.size() - 1; i++) {
	int min = i;
	for (int j = i + 1; j < a.size(); j++) {
	    if (a[j] < a[min])
		min = j;
	}
	std::swap(a[min], a[i]);
    }
}

void
Insertion::sort(std::vector<Comparable> &a) {
    for (int i = 1; i < a.size(); i++) {
	for (int j = i; j > 0 && a[j] < a[j - 1]; j--) {
	    std::swap(a[j], a[j - 1]); // every location, read & write twice
	}
    }
}

void
Insertion::sort2(std::vector<Comparable> &a) {
    for (int i = 1; i < a.size(); i++) {
	int cur = i;
	Comparable tmp = a[i];
	while (cur > 0 && tmp < a[cur - 1])
	    cur--;

	for (int j = i; j > cur; j--)
	    a[j] = a[j - 1]; // every location, read & write once
	a[cur] = tmp;
    }
}

void STL::sort(std::vector<Comparable> &a) {
    std::sort(a.begin(), a.end());
}

double
Sort_Compare::time(const Sort_Function &func, std::vector<Comparable> &a) {
    auto start = std::chrono::steady_clock::now();
    func(a);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    return elapsed_seconds.count();
}

double
Sort_Compare::time_random_input(const Sort_Function &func, int array_len, int loop_times) {
    std::vector<Comparable> a(array_len);
    double total = 0.0;

    ::srandom(::time(NULL));

    for (int t = 0; t < loop_times; t++) {
	for (int i = 0; i < array_len; i++)
	    a[i] = ::random();
	total += time(func, a);
    }

    return total;
}

#define TEST_ARRAY_LENGTH 10
void
Sort_Compare::test_sort(const std::string &alg, const Sort_Function &func) {
    std::cout << "<<<Test " << alg << " sort algorithm>>>" << std::endl;

    std::vector<Comparable> a(TEST_ARRAY_LENGTH);
    ::srandom(::time(NULL));

    std::cout << "Initial array:" << std::endl;
    for (int i = 0; i < TEST_ARRAY_LENGTH; i++)
    {
	a[i] = ::random() % 100;
	std::cout << a[i] << ' ';
    }
    std::cout << std::endl;

    func(a);

    std::cout << "Sorted array:" << std::endl;
    for (auto &n : a)
	std::cout << n << ' ';
    std::cout << std::endl;
}
#undef TEST_ARRAY_LENGTH
