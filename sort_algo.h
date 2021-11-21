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
    static void sort(Comparable_Array&); 
    static void sort2(Comparable_Array&); 
};

struct Shell {
    static void sort(Comparable_Array&);
    static void sort2(Comparable_Array&);
};

struct Sort_Compare {
    static double sort_and_time(const Sort_Function&, Comparable_Array&);
    static double sort_and_time_random_input(const Sort_Function&, int, int);
    static void test_sort_algo(const std::string&, const Sort_Function&);
};

struct Sort_Registration {
    static const Name_Sort_Function_Map& algos(); 
};
