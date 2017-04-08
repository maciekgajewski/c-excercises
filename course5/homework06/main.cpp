#include <iostream>
#include <cassert>
#include "string.h"
#include "test.h"

template <typename T>
void run_all_tests(TestClass<T> & test)
{
    test.test_const_char_constructor();
    test.test_move_constructor();
    test.test_copy_assignment();
    test.test_move_assignment();
    test.test_assignment_from_c_str();
    test.test_const_index_operator();
    test.test_index_operatior();
    test.test_concat_operator();
    test.test_concat_same_string_operator();
    test.test_c_srt();
    test.test_length();
    test.test_size();
}

int main()
{
    auto test = TestClass<std::string>();
    //run_all_tests(test);
    auto test2 = TestClass<String>();
    run_all_tests(test2);
    return 0;
}

