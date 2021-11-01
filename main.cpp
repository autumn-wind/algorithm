#include<string>

#include<stdio.h>
#include<stdlib.h>
#include"sort_algo.h"

#define ARRAY_LENGTH 1000
#define LOOP_NUM 100

void print_usage_and_exit() {
	printf("Wrong usage. Below are the right ones:\n\
		./a.out test Insertion\n\
		./a.out Insertion Selection\n\
		./a.out Insertion Selection 100 1000\n");
	exit(EXIT_FAILURE);
}

int main(int argn, char *argv[]) {
    if (argn < 3 || argn > 5) {
	print_usage_and_exit();
    }

    std::string alg1 = argv[1], alg2 = argv[2];
    auto &algo_list = Sort_Registration::algos();

    if (alg1.compare("test") == 0) {
	// TODO: test whether algorithm works well
	if (algo_list.find(alg2) != algo_list.end() && argn == 3)
	    exit(0);
	else
	    print_usage_and_exit();
    }
    else {
	// compare two algorithms
	if (algo_list.find(alg1) != algo_list.end() && algo_list.find(alg2) != algo_list.end()) {
	    int array_len = argn >= 4 ? atoi(argv[3]) : ARRAY_LENGTH;
	    int loop_num = argn >= 5 ? atoi(argv[4]) : LOOP_NUM;

	    double t1 = Sort_Compare::time_random_input(alg1, array_len, loop_num);
	    double t2 = Sort_Compare::time_random_input(alg2, array_len, loop_num);

	    printf("For %d random Ints of %d iteration\n\
		    %s (takes %f seconds) is %.1f times faster than %s (takes %f seconds)\n", 
		    array_len, loop_num, alg1.c_str(), t1, t2/t1, alg2.c_str(), t2);
	}
	else
	    print_usage_and_exit();
    }

    return 0;
}
