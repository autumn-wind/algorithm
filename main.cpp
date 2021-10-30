#include<string>
#include<stdio.h>
#include<stdlib.h>
#include"sort_algo.h"

int main(int argn, char *argv[]) {
    std::string alg1 = argv[1], alg2 = argv[2];
    int N = atoi(argv[3]), T = atoi(argv[4]);

    double t1 = Sort_Compare::time_random_input(alg1, N, T);
    double t2 = Sort_Compare::time_random_input(alg2, N, T);

    printf("For %d random Ints of %d iteration\n\
	    %s (takes %f seconds) is %.1f times faster than %s (takes %f seconds)\n", 
	    N, T, alg1.c_str(), t1, t2/t1, alg2.c_str(), t2);

    return 0;
}
