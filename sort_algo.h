#include<vector>
#include<string>
#include<map>
#include<functional>

typedef int Comparable;
typedef std::vector<Comparable> Comparable_Array;
typedef std::function<void(Comparable_Array&)> Sort_Function;
typedef std::map<std::string, Sort_Function> Name_Sort_Function_Map;

struct STL {
    static void sort(Comparable_Array&);
};

struct Selection {
    static void sort(Comparable_Array&);
};

struct Insertion {
	static void do_sort(Comparable_Array&, int, int);
    static void sort(Comparable_Array&);
	static void do_sort2(Comparable_Array&, int, int);
    static void sort2(Comparable_Array&);
};

struct Shell {
    static void sort(Comparable_Array&);
    static void sort2(Comparable_Array&);
    static void sort3(Comparable_Array&);
};

struct Merge {
    static void do_merge(Comparable_Array&, Comparable_Array&, int, int, int);
    static void do_sort(Comparable_Array&, Comparable_Array&, int, int);
    static void sort(Comparable_Array&);
    static void do_sort2(Comparable_Array&, Comparable_Array&, int, int);
    static void sort2(Comparable_Array&);
    static void do_sort3(Comparable_Array&, Comparable_Array&, int, int);
    static void sort3(Comparable_Array&);
    static void do_merge4(Comparable_Array&, Comparable_Array&, int, int, int);
    static void do_sort_aux_to_ori(Comparable_Array&, Comparable_Array&, int, int);
    static void do_sort_ori_to_aux(Comparable_Array&, Comparable_Array&, int, int);
    static void sort4(Comparable_Array&);
};

struct Sort_Compare {
    static double sort_and_time(const Sort_Function&, Comparable_Array&);
    static double sort_and_time_random_input(const Sort_Function&, int, int);
    static void test_sort_algo(const std::string&, const Sort_Function&);
};

struct Sort_Registration {
    static const Name_Sort_Function_Map& algos();
};
