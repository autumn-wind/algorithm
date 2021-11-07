#include<vector>
#include<string>
#include<map>
#include<functional>

#define Comparable int

typedef std::function<void(std::vector<Comparable>&)> Sort_Function;
typedef std::map<std::string, Sort_Function> String_Function_Map;

struct Selection {
    static void sort(std::vector<Comparable>&);
};

struct Insertion {
    static void sort(std::vector<Comparable>&); 
    static void sort2(std::vector<Comparable>&); 
};

struct STL {
    static void sort(std::vector<Comparable>&);
};

struct Sort_Compare {
    static double time(const Sort_Function&, std::vector<Comparable>&);
    static double time_random_input(const Sort_Function&, int, int);
    static void test_sort(const std::string&, const Sort_Function&);
};

struct Sort_Registration {
    static const String_Function_Map& algos(); 
};
