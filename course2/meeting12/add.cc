#include "add.h"

int global;

struct Stats
{
    int calls = 0;
    int totalA = 0;
    int totalB = 0;
};

Stats global_stats;

Stats& get_stats() { return global_stats; }

int add(Stats& s, int a, int b)
{
    s.calls ++;
    s.totalA += a;
    s.totalB += b;
    
    return a+b+global;
}