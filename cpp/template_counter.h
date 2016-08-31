#ifndef counter_h
#define counter_h


template <int index>
struct print_indexes_down
{
    static void print()
    {
        std::cout << index << std::endl;
        print_indexes_down<index-1>::print();
    }
};
    

template<>
struct print_indexes_down<0>
{
    static void print()
    {
        std::cout << 0 << std::endl;
    }
};


template <int index, int x = 0>
struct print_indexes_up
{
    static void print()
    {
        std::cout << x << std::endl;
        print_indexes_up<index-1, x+1>::print();
    }
};
    

template<int x>
struct print_indexes_up<0, x>
{
    static void print()
    {
        std::cout << x << std::endl;
    }
};

#endif

