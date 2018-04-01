#include "complex.h"
#include "operation.h"
#include "parser.h"
#include "stack.h"
#include <boost/filesystem.hpp>
#include <dlfcn.h>
#include <map>
#include <stack>

namespace fs = boost::filesystem;

using Stack = std::stack<Complex, MyComplexLinkedList>;
using invoke_command = void (*)(Stack&);
using get_char = char (*)();

std::ostream& operator<<(std::ostream& s, Stack& stack)
{
    Stack tmp_stack;
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

void load_command_implementation(std::map<char, invoke_command>& operations, const fs::path& path)
{
    auto lib = dlopen(path.c_str(), RTLD_NOW);
    if (!lib) {
        std::cerr << dlerror() << std::endl;
        return;
    }

    get_char get_command_name = reinterpret_cast<get_char>(dlsym(lib, "get_command_name"));
    invoke_command ik = reinterpret_cast<invoke_command>(dlsym(lib, "invoke_command"));

    if (!get_command_name || !ik) {
        std::cerr << dlerror() << std::endl;
        return;
    }

    char c = (*get_command_name)();
    operations.insert(std::pair<char, invoke_command>(c, ik));
}

std::map<char, invoke_command> load_commands_implementations()
{
    std::map<char, invoke_command> command_to_implementation;

    for (auto& entry : fs::directory_iterator(fs::current_path()))
        if (fs::is_regular_file(entry) && ".so" == entry.path().extension())
            load_command_implementation(command_to_implementation, entry.path());

    return command_to_implementation;
}

bool try_handle_with_plugin(Stack& stack, const std::map<char, invoke_command>& command_to_implementation, const char c)
{
    auto it = command_to_implementation.find(c);
    if (it == command_to_implementation.end())
        return false;

    invoke_command ik = it->second;
    (*ik)(stack);
    return true;
}

void apply_static_handler(Stack& stack, const char command)
{
    switch(command) {
    case 'c': // clear
        while(!stack.empty())
            stack.pop();
        break;
    case 'f': // full print
        std::cout << stack;
        break;
    case 'p': // print top
        std::cout << stack.top() << std::endl;
        break;
    default:
        std::cerr << "Not implemented: '" << command << "'" << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::map<char, invoke_command> command_to_implementation = load_commands_implementations();
    Stack stack;
    Parser parser(std::cin);

    while(!parser.eof()) {
        if (parser.number_is_comming()) {
            stack.push(parser.read_number());
        }
        else {
            char command = parser.read_command();

            if(!try_handle_with_plugin(stack, command_to_implementation, command))
                apply_static_handler(stack, command);
        }
    }
}
