#define Comparable int

struct Selection {
    static void sort(std::vector<Comparable>&);
};

struct Insertion {
    static void sort(std::vector<Comparable>&); 
    static void sort2(std::vector<Comparable>&); 
};

struct Sort_Compare {
    static double time(std::string&, std::vector<Comparable>&);
    static double time_random_input(std::string&, int, int);
};
