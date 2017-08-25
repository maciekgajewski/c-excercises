#include "ustring.h"

#include <algorithm>
#include <cassert>
#include <vector>
#include <random>

#include <iostream>

int main()
{
    using namespace Course;
    String s1("Mokus felmaszott a fara");
    String s2("Mokus felmaszott egy fara");
    assert(std::any_of(std::begin(s1), std::end(s1), [](char c){ return c == ' '; }));
    assert(std::count(std::begin(s1), std::end(s1), 'a') == 4);
    assert((std::mismatch(std::begin(s1), std::end(s1), std::begin(s2)).first - std::begin(s1)) == 17);

    std::vector<char> v1;
    std::copy(std::begin(s1), std::end(s1), std::back_inserter(v1));
    assert(std::equal(std::begin(s1), std::end(s1), v1.begin()));

    String encrypted;
    std::transform(std::begin(s1), std::end(s1), std::back_inserter(encrypted), [](auto c) {
                return (c>= 'A' && c <= 'Z') ? ((c-'A'+3)%26+'A') :
                    ((c>= 'a' && c <= 'z') ? (c-'a'+3)%26+'a' : c);
            });
    std::cout << encrypted << std::endl;

    std::random_device rdev;
    std::mt19937 random_gen(rdev());

    String s3 = s1;
    std::shuffle(s3.begin(), s3.end(), random_gen);
    std::cout << s3 << std::endl;
}
