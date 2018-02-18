#include "complex.h"
#include "operation.h"
#include "parser.h"
#include <boost/filesystem.hpp>
#include <dlfcn.h>
#include <iostream>
#include <stack>
#include <map>

namespace fs = boost::filesystem;

using operation = void (*)(std::stack<Complex>&);
using get_char = char (*)();

std::ostream& operator<<(std::ostream& s, std::stack<Complex>& stack)
{
    std::stack<Complex> tmp_stack;
    while(!stack.empty()) {
        s << stack.top() << std::endl;
        tmp_stack.push(stack.top());
        stack.pop();
    }

    while(!tmp_stack.empty()) {
        stack.push(tmp_stack.top());
        tmp_stack.pop();
    }
    return s;
}

void load_operation_implementation(std::map<char, operation>& operations, const fs::path& path)
{
    auto lib = dlopen(path.c_str(), RTLD_NOW);
    if (!lib) {
        std::cerr << dlerror() << std::endl;
        return;
    }

    get_char get_op_char = (get_char)dlsym(lib, "get_operation_symbol");
    operation op = (operation)dlsym(lib, "operation");

    if (!get_op_char || !op) {
        std::cerr << dlerror() << std::endl;
        return;
    }

    char c = (*get_op_char)();
    operations.insert(std::pair<char, operation>(c, op));
}

std::map<char, operation> load_operations_implementations()
{
    std::map<char, operation> char_to_operation;

    for (auto& entry : fs::directory_iterator(fs::current_path()))
        if (fs::is_regular_file(entry) && ".so" == entry.path().extension())
            load_operation_implementation(char_to_operation, entry.path());

    return char_to_operation;
}

operation try_get_operation(std::map<char, operation>& char_to_operation, char c)
{
    auto it = char_to_operation.find(c);
    if (it == char_to_operation.end())
        return nullptr;
    else
        return it->second;
}

void clear(std::stack<Complex>& stack)
{
    while(!stack.empty())
        stack.pop();
}

void try_apply_command(std::stack<Complex>& stack, const char command)
{
    switch(command) {
    case 'c':
        clear(stack);
        break;
    case 'f':
        std::cout << stack;
        break;
    case 'p':
        std::cout << stack.top() << std::endl;
        break;
    default:
        std::cerr << "Not implemented: '" << command << "'" << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::map<char, operation> command_to_operation = load_operations_implementations();
    std::stack<Complex> stack;
    Parser parser(std::cin);

    std::cin >> std::ws;
    while(!parser.eof()) {
        if (parser.number_is_comming()) {
            stack.push(parser.read_number());
        }
        else {
            char command = parser.get_command();

            operation op = try_get_operation(command_to_operation, command);
            if (op) {
                if (parser.extempt_is_applicable())
                    stack.push(parser.read_number());

                (*op)(stack);
            }
            else {
                try_apply_command(stack, command);
            }
        }
    }
}
