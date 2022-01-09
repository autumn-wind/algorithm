#include<chrono>
#include<algorithm>
#include<vector>
#include<algorithm>

#include<time.h>

#include"sort_algo.h"

const Name_Sort_Function_Map&
Sort_Registration::algos() {
	static Name_Sort_Function_Map sort_algorithms {
		{"STL", STL::sort},

		{"Selection", Selection::sort},

		{"Insertion", Insertion::sort},
		{"Insertion_rw_once", Insertion::sort_rw_once},

		{"Shell", Shell::sort},
		{"Shell_by_static_steps", Shell::sort_by_static_steps},
		{"Shell_by_adv_static_steps", Shell::sort_by_adv_static_steps},

		{"Merge", Merge::sort},
		{"Merge_using_insertion_sort", Merge::sort_using_insertion_sort},
		{"Merge_pruning_merge", Merge::sort_pruning_merge},
		{"Merge_without_copy", Merge::sort_without_copy},
		{"Merge_from_bottom_to_top", Merge::sort_from_bottom_to_top},

		{"Quick", Quick::sort},
		{"Quick_3_way", Quick::sort_3_way},
	};
	return sort_algorithms;
}

void STL::sort(Comparable_Array &a) {
	std::sort(a.begin(), a.end());
}

void
Selection::sort(Comparable_Array &a) {
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
Insertion::do_sort(Comparable_Array &a, int lo, int hi) {
	for (int i = lo + 1; i <= hi; i++)
		for (int j = i; j > lo && a[j] < a[j - 1]; j--)
			std::swap(a[j], a[j - 1]); // every location, read & write twice
}

void
Insertion::sort(Comparable_Array &a) {
	do_sort(a, 0, a.size() - 1);
}

void
Insertion::do_sort_rw_once(Comparable_Array &a, int lo, int hi) {
	for (int i = lo + 1; i <= hi; i++) {
		int cur = i;
		Comparable tmp = a[i];
		while (cur > lo && tmp < a[cur - 1])
			cur--;
		for (int j = i; j > cur; j--)
			a[j] = a[j - 1]; // every location, read & write once
		a[cur] = tmp;
	}
}

void
Insertion::sort_rw_once(Comparable_Array &a) {
	do_sort_rw_once(a, 0, a.size() - 1);
}

void
Shell::sort(Comparable_Array &a) {
	int h = 1, N = a.size();
	while (h < N / 3)
		h = h * 3 + 1;

	while (h >= 1) {
		for (int i = h; i < N; i++)
			for (int j = i; j - h >= 0 && a[j] < a[j - h]; j -= h)
				std::swap(a[j], a[j - h]);
		h /= 3;
	}
}

void
Shell::sort_by_static_steps(Comparable_Array &a) {
	const std::vector<int> sequence = {1, 4, 13, 40, 121, 364, 1093, 3280, 9841, 29524, 88573, 265720};
	int N = a.size();
	for (int hi = sequence.size() - 1; hi >= 0; hi--) {
		int h = sequence[hi];
		for (int i = h; i < N; i++)
			for (int j = i; j - h >= 0 && a[j] < a[j - h]; j -= h)
				std::swap(a[j], a[j - h]);
	}
}

void
Shell::sort_by_adv_static_steps(Comparable_Array &a) {
	const std::vector<int> sequence = {1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001, 36289, 64769, 146305, 260609};
	int N = a.size();
	for (int hi = sequence.size() - 1; hi >= 0; hi--) {
		int h = sequence[hi];
		for (int i = h; i < N; i++)
			for (int j = i; j - h >= 0 && a[j] < a[j - h]; j -= h)
				std::swap(a[j], a[j - h]);
	}
}

void
Merge::do_merge(Comparable_Array &a, Comparable_Array &aux, int lo, int mid, int hi) {
	for (int k = lo; k <= hi; k++)
		aux[k] = a[k];

	int i = lo, j = mid + 1;
	for (int k = lo; k <= hi; k++) {
		if (i > mid)
			a[k] = aux[j++];
		else if (j > hi)
			a[k] = aux[i++];
		else if (aux[i] < aux[j])
			a[k] = aux[i++];
		else
			a[k] = aux[j++];
	}
}

void
Merge::do_sort(Comparable_Array &a, Comparable_Array &aux, int lo, int hi) {
	if (lo >= hi)
		return;

	int mid = lo + (hi - lo) / 2;
	do_sort(a, aux, lo, mid);
	do_sort(a, aux, mid + 1, hi);
	do_merge(a, aux, lo, mid, hi);
}

void
Merge::sort(Comparable_Array &a) {
	Comparable_Array aux(a.size(), 0);
	do_sort(a, aux, 0, a.size() - 1);
}

void
Merge::do_sort_using_insertion_sort(Comparable_Array &a, Comparable_Array &aux, int lo, int hi) {
	// use insertion sort for small array
	if (hi - lo < 15)
		return Insertion::do_sort(a, lo, hi);

	int mid = lo + (hi - lo) / 2;
	do_sort_using_insertion_sort(a, aux, lo, mid);
	do_sort_using_insertion_sort(a, aux, mid + 1, hi);
	do_merge(a, aux, lo, mid, hi);
}

void
Merge::sort_using_insertion_sort(Comparable_Array &a) {
	Comparable_Array aux(a.size(), 0);
	do_sort_using_insertion_sort(a, aux, 0, a.size() - 1);
}

void
Merge::do_sort_pruning_merge(Comparable_Array &a, Comparable_Array &aux, int lo, int hi) {
	if (lo >= hi)
		return;

	int mid = lo + (hi - lo) / 2;
	do_sort_pruning_merge(a, aux, lo, mid);
	do_sort_pruning_merge(a, aux, mid + 1, hi);
	// avoid unnecessary merge
	if (a[mid] > a[mid + 1])
		do_merge(a, aux, lo, mid, hi);
}

void
Merge::sort_pruning_merge(Comparable_Array &a) {
	Comparable_Array aux(a.size(), 0);
	do_sort_pruning_merge(a, aux, 0, a.size() - 1);
}

void
Merge::do_merge_without_copy(Comparable_Array &a, Comparable_Array &aux, int lo, int mid, int hi) {
	int i = lo, j = mid + 1;
	for (int k = lo; k <= hi; k++) {
		if (i > mid)
			a[k] = aux[j++];
		else if (j > hi)
			a[k] = aux[i++];
		else if (aux[i] < aux[j])
			a[k] = aux[i++];
		else
			a[k] = aux[j++];
	}
}

// directly sort array a into array aux
void
Merge::do_sort_without_copy(Comparable_Array &a, Comparable_Array &aux, int lo, int hi) {
	if (lo >= hi)
		return;

	int mid = lo + (hi - lo) / 2;
	do_sort_without_copy(aux, a, lo, mid);
	do_sort_without_copy(aux, a, mid + 1, hi);
	do_merge_without_copy(aux, a, lo, mid, hi);
}

// merge without copying
void
Merge::sort_without_copy(Comparable_Array &a) {
	Comparable_Array aux(a.begin(), a.end());
	int lo = 0, hi = a.size() - 1;
	int mid = lo + (hi - lo) / 2;
	do_sort_without_copy(a, aux, lo, mid);
	do_sort_without_copy(a, aux, mid + 1, hi);
	do_merge_without_copy(a, aux, lo, mid, hi);
}

// merge sort from bottom to top
void
Merge::sort_from_bottom_to_top(Comparable_Array &a) {
	int N = a.size();
	Comparable_Array aux(N, 0);
	for (int sz = 1; sz < N; sz *= 2)
		for (int lo = 0; lo + sz < N; lo += 2 * sz)
			do_merge(a, aux, lo, lo + sz - 1, std::min(lo + 2 * sz - 1, N - 1));
}

int
Quick::partition(Comparable_Array &a, int lo, int hi) {
	int i = lo, j = hi + 1;
	Comparable v = a[lo];
	while (true) {
		while (a[++i] < v) if (i == hi) break;
		while (a[--j] > v) /*if (j == lo) break*/;
		if (i >= j) break;
		std::swap(a[i], a[j]);
	}
	std::swap(a[lo], a[j]);
	return j;
}

void
Quick::do_sort(Comparable_Array &a, int lo, int hi) {
	if (lo >= hi)
		return;
	int j = partition(a, lo, hi);
	do_sort(a, lo, j - 1);
	do_sort(a, j + 1, hi);
}

void
Quick::sort(Comparable_Array &a) {
	std::random_shuffle(a.begin(), a.end());
	do_sort(a, 0, a.size() - 1);
}

// quick-3-way
void
Quick::do_sort_3_way(Comparable_Array &a, int lo, int hi) {
	if (lo >= hi)
		return;
	Comparable v = a[lo];
	int lt = lo, i = lo + 1, gt = hi;
	while (i <= gt) {
		if (a[i] < v)
			std::swap(a[i++], a[lt++]);
		else if (a[i] > v)
			std::swap(a[i], a[gt--]);
		else
			i++;
	}
	do_sort_3_way(a, lo, lt - 1);
	do_sort_3_way(a, gt + 1, hi);
}

void
Quick::sort_3_way(Comparable_Array &a) {
	std::random_shuffle(a.begin(), a.end());
	do_sort_3_way(a, 0, a.size() - 1);
}

double
Sort_Compare::sort_and_time(const Sort_Function &func, Comparable_Array &a) {
	auto start = std::chrono::steady_clock::now();
	func(a);
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	return elapsed_seconds.count();
}

double
Sort_Compare::sort_and_time_random_input(const Sort_Function &func, int array_len, int loop_times) {
	Comparable_Array a(array_len);
	double total = 0.0;

	::srandom(::time(NULL));

	for (int t = 0; t < loop_times; t++) {
		for (int i = 0; i < array_len; i++)
			a[i] = ::random();
		total += sort_and_time(func, a);
	}

	return total;
}

bool
Sort_Compare::test_sort_algo(const std::string &alg, const Sort_Function &func) {
	Comparable_Array a(DEFAULT_ARRAY_LENGTH), b(DEFAULT_ARRAY_LENGTH);

	::srandom(::time(NULL));

	for (int t = 0; t < DEFAULT_LOOP_TIMES; t++)
	{
		for (int i = 0; i < DEFAULT_ARRAY_LENGTH; i++) {
			a[i] = ::random();
			b[i] = a[i];
		}

		func(a);
		STL::sort(b);

		for (int i = 0; i < DEFAULT_ARRAY_LENGTH; i++)
			if (a[i] != b[i])
				return false;
	}

	return true;
}
