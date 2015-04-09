#include <iostream>
#include <stdexcept>
#include <string>
#include <functional>
#include <vector>
#include <cassert>

template<typename Cleanup>
struct AtExit
{
    AtExit(Cleanup c) : mCleanup(c) {}
    ~AtExit() { mCleanup(); }
    Cleanup mCleanup;
};

template<typename Cleanup>
AtExit<Cleanup> at_exit(Cleanup c) { return AtExit<Cleanup>(c); }

class Signal
{
public:
    using Fun = std::function<void()>;
    
    std::exception_ptr activate() noexcept
    {
        mIterating = true;
        auto ae = at_exit([=] { mIterating = false; });
        
        for(const Fun& f : mFunctions)
        {
            try
            {
                f();
            }
            catch(...)
            {
                std::exception_ptr ex = std::current_exception();
                return ex;
            }
        }
        
        return false;
    }
    
    void subscribe(const Fun& f)
    {
        assert(!mIterating);
        mFunctions.push_back(f);
    }
    
private:
    std::vector<Fun> mFunctions;
    bool mIterating = false;
};

void fun1()
{
    std::cout <<"this is fun1" << std::endl;
    //throw std::runtime_error("Some exception");
    throw 33;
}

void fun2() { std::cout << "fun2" << std::endl;  }

int main(int argc, char ** argv)
{
    Signal sig;
    sig.subscribe(fun1);
    sig.subscribe(fun2);
    sig.subscribe(fun1);
    
    try
    {
        auto e = sig.activate();
        if(e)
        {
            std::cout << "There were errors: ";
            try{ std::rethrow_exception(e);  }
            catch(const std::exception& ee) { std::cout << ee.what() << std::endl; }
            catch(...) { std::cout << "unknown type" << std::endl; }
        }
    }
    catch(const std::exception& e)
    {
        std::cout << "Error in 'activate' : " << e.what() << std::endl;
    }
    sig.subscribe(fun2);
}
