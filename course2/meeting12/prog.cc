#include "add.h"

extern int global;

int main(int argc, char** argv)
{
    global = 55;
    
    Stats& stats = get_stats();
    
    return add(stats, argc, 7);
}