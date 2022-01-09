#include<vector>
#include<string>
#include<map>
#include<functional>

typedef int Comparable;
typedef std::vector<Comparable> Comparable_Array;
typedef std::function<void(Comparable_Array&)> Sort_Function;
typedef std::map<std::string, Sort_Function> Name_Sort_Function_Map;

#define DEFAULT_ARRAY_LENGTH 1000
#define DEFAULT_LOOP_TIMES 100

struct STL {
    static void sort(Comparable_Array&);
};

struct Selection {
    static void sort(Comparable_Array&);
};

struct Insertion {
	static void do_sort(Comparable_Array&, int, int);
    static void sort(Comparable_Array&);

	static void do_sort_rw_once(Comparable_Array&, int, int);
    static void sort_rw_once(Comparable_Array&);
};

struct Shell {
    static void sort(Comparable_Array&);

    static void sort_by_static_steps(Comparable_Array&);

    static void sort_by_adv_static_steps(Comparable_Array&);
};

struct Merge {
    static void do_merge(Comparable_Array&, Comparable_Array&, int, int, int);
    static void do_sort(Comparable_Array&, Comparable_Array&, int, int);
    static void sort(Comparable_Array&);

    static void do_sort_using_insertion_sort(Comparable_Array&, Comparable_Array&, int, int);
    static void sort_using_insertion_sort(Comparable_Array&);

    static void do_sort_pruning_merge(Comparable_Array&, Comparable_Array&, int, int);
    static void sort_pruning_merge(Comparable_Array&);

    static void do_merge_without_copy(Comparable_Array&, Comparable_Array&, int, int, int);
    static void do_sort_without_copy(Comparable_Array&, Comparable_Array&, int, int);
    static void sort_without_copy(Comparable_Array&);

	static void sort_from_bottom_to_top(Comparable_Array&);
};

struct Quick {
    static int partition(Comparable_Array&, int, int);
    static void do_sort(Comparable_Array&, int, int);
    static void sort(Comparable_Array&);

    static void do_sort_3_way(Comparable_Array&, int, int);
    static void sort_3_way(Comparable_Array&);
};

struct Sort_Compare {
    static double sort_and_time(const Sort_Function&, Comparable_Array&);
    static double sort_and_time_random_input(const Sort_Function&, int, int);
    static bool test_sort_algo(const std::string&, const Sort_Function&);
};

struct Sort_Registration {
    static const Name_Sort_Function_Map& algos();
};
