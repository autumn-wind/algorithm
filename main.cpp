#include<string>

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"sort_algo.h"

void print_usage_and_exit() {
	printf("Wrong usage. Below are some right examples:\n\
		./a.out test Selection\n\
		./a.out time Insertion\n\
		./a.out time Insertion 100\n\
		./a.out time Insertion 100 1000\n\
		./a.out Insertion Selection\n\
		./a.out Insertion Selection 100\n\
		./a.out Insertion Selection 100 1000\n");
	exit(EXIT_FAILURE);
}

int main(int argn, char *argv[]) {
	if (argn < 3 || argn > 5) {
		print_usage_and_exit();
	}

	const std::string alg1 = argv[1], alg2 = argv[2];
	const auto &algo_list = Sort_Registration::algos();
	auto it1 = algo_list.find(alg1);
	auto it2 = algo_list.find(alg2);

	// test whether algorithm works well
	if (alg1.compare("test") == 0 && it2 != algo_list.end() && argn == 3) {
		bool success = Sort_Compare::test_sort_algo(alg2, it2->second);
		if (success)
			printf("%s sort algorithm passes all tests\n", alg2.c_str());
		else
			printf("%s sort algorithm fails at least one test\n", alg2.c_str());
	}
	else {
		int array_len = DEFAULT_ARRAY_LENGTH;
		int loop_times = DEFAULT_LOOP_TIMES;
		if (argn >= 4) {
			int res = atoi(argv[3]);
			if (res > 0)
				array_len = res;
			else
				print_usage_and_exit();
		}
		if (argn >= 5) {
			int res = atoi(argv[4]);
			if (res > 0)
				loop_times = res;
			else
				print_usage_and_exit();
		}

		// time the algorithm
		if (alg1.compare("time") == 0 && it2 != algo_list.end()) {
			double t = Sort_Compare::sort_and_time_random_input(it2->second, array_len, loop_times);
			printf("For %d random Ints of %d iteration\n%s (takes %f seconds)\n",
			       array_len, loop_times, alg2.c_str(), t);
		}
		// compare two algorithms
		else if (it1 != algo_list.end() && it2 != algo_list.end()) {
			sleep(1);
			double t1 = Sort_Compare::sort_and_time_random_input(it1->second, array_len, loop_times);
			sleep(1);
			double t2 = Sort_Compare::sort_and_time_random_input(it2->second, array_len, loop_times);

			printf("For %d random Ints of %d iteration\n\
		    %s (takes %f seconds) is %.3f times faster than %s (takes %f seconds)\n",
			       array_len, loop_times, alg1.c_str(), t1, t2 / t1, alg2.c_str(), t2);
		}
		else
			print_usage_and_exit();
	}

	return 0;
}
