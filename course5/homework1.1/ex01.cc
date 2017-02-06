#include <iostream>
#include <stdlib.h>
#include <string.h>

// ARS - 20170206
// qsort example from qsort manual

static int cmpstringp(const void *p1, const void *p2)
{
   /* The actual arguments to this function are "pointers to
              pointers to char", but strcmp(3) arguments are "pointers
              to char", hence the following cast plus dereference */

   return strcmp(* (char * const *) p1, * (char * const *) p2);
}

int main(int argc, char** argv)
{
    if (argc > 1)
    {
	qsort(&argv[1], argc - 1, sizeof(char *), cmpstringp);
	for (int i = 1; i < argc; i ++)
	{
		std::cout << argv[i] << std::endl;
	}
    }
    return 0;
}

