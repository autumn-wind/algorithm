#include<vector>
#include<string>
#include<chrono>
#include<stdlib.h>
#include<time.h>
#include"sort_algo.h"

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

double
Sort_Compare::time(std::string &alg, std::vector<Comparable> &a) {
    auto start = std::chrono::steady_clock::now();
    if (alg.compare("Selection") == 0)
	Selection::sort(a);
    else if (alg.compare("Insertion") == 0)
	Insertion::sort(a);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    return elapsed_seconds.count();
}

double
Sort_Compare::time_random_input(std::string &alg, int N, int T) {
    double total = 0.0;
    std::vector<Comparable> a(N);
    ::srandom(::time(NULL));
    for (int t = 0; t < T; t++) {
	for (int i = 0; i < N; i++)
	    a[i] = ::random();
	total += time(alg, a);
    }
    return total;
}
