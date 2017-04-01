#include "unique.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stdexcept>

int main(int, char**)
{
    course::unique_ptr<int> p;
    assert( p.get() == nullptr );
    p = course::make_unique<int>();
    assert( p.get() != nullptr );
    *p.get() = 1;
    assert( *p.get() == 1);

    course::unique_ptr<int> q = std::move(p);
    assert( p.get() == nullptr );
    assert( *q.get() == 1 );
    course::unique_ptr<int> r = course::make_unique<int>();
    *r.get() = 2;
    q = std::move(r);
    assert( *q.get() == 2 );
}