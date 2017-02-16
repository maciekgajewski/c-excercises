#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>

struct FuncInspectMetadata
{
    std::vector<void*> ptr_to_local;
};

// compiler: gcc-4.9, linux AMD64 ABI
// In debug build, stack frame size is 64 byte, compiler generated a recursive function call.
// In release build, compiler optimized out the recursive function call.
// The stack grows from the higher address to the lower on this ABI.
float newton_sqrt(float number, float guess, FuncInspectMetadata &metadata)
{
    static constexpr float EPSILON = 1.0e-8;
    metadata.ptr_to_local.push_back(&guess);
    if (std::abs(guess*guess - number) < EPSILON) return guess;
    return newton_sqrt(number, guess - ((guess*guess - number) / (2*guess)), metadata);
}

int main()
{
    for (int i=1; i<100; ++i)
    {
        float x = (i/10.0f)*(i/10.0f);
        FuncInspectMetadata meta;
        float newton = newton_sqrt(x, x, meta);
        auto depth = meta.ptr_to_local.size();
        auto diff = reinterpret_cast<char*>(meta.ptr_to_local.front()) - reinterpret_cast<char*>(meta.ptr_to_local.back());
        size_t stack_frame_depth = 0;
        if (meta.ptr_to_local.size() > 1)
        {
            stack_frame_depth = diff / (meta.ptr_to_local.size()-1);
            void *prev=meta.ptr_to_local.front();
            for (auto it=meta.ptr_to_local.begin()+1; it<meta.ptr_to_local.end(); ++it)
            {
                std::cout << reinterpret_cast<char*>(prev) - reinterpret_cast<char*>(*it) << std::endl;
                prev = *it;
            }
        }
        std::cout << "newton_sqrt(" << x << ") => " << newton << " recursion depth:" << depth << " stack frame size:" << stack_frame_depth << std::endl;
    }
}
