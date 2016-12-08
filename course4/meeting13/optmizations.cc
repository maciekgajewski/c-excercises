// optimization examples

// calling conv: 
// params in: RDI, RSI, RDX, RCX 
// return in accu

// simple inlining ////////////////////////////////

static int triple(int v)
{
  return v *3;
}


int calculate(int a, int b)
{
  return a + triple(b);
}


// 0-cost abstractions - unique_ptr //////////////////////////

#include <memory>


int use_data(int* dest, int size);

int fun1(int size)
{
  int* data = new int[size];
  int result = use_data(data, size);
  delete data;
  return result;
}

int fun2(int size)
{
  auto data = std::make_unique<int[]>(size);
  return use_data(data.get(), size);
}

// 0-cost abstractions - algos /////////////////////////////////
#include <numeric>

int total1(int* data, int size)
{
	int r = 0;
	for(int i = 0; i < size; i++)
		r += data[i];
	return r;
}

int total2(int* data, int size)
{
	return std::accumulate(data, data+size, 0);
}

// unsignedvs signed 1 + const propagation //////////////////////////
#include <memory>

std::unique_ptr<double[]> alloc_array1(int size)
{
	return std::make_unique<double[]>(size);
}

std::unique_ptr<double[]> alloc_array2(unsigned size)
{
	return std::make_unique<double[]>(size);
}

std::unique_ptr<double[]> alloc_array3()
{
	return alloc_array2(11);
}

// const propagation /////////////////////////////

int GLOBAL = 7;// try const, try static, try static+setter

int mul_glob(int m) { return GLOBAL*m; }

int value()
{
  return mul_glob(3);
}

// branch reduction  /////////////////////////////////////
#include <vector>
#include <cassert>

void populate(std::vector<double>& v)
{
	//assert(v.size() > 0);
	v.at(0) = 4.4;
}

// dead branch removal ////////////////////

void foo();
void bar();

void action(unsigned i)
{
	if (i < 0 )
		foo();
	else
		bar();
}

// jump threading + tail call optimization /////////////////////////
void foo();
void bar();

void callif(bool cond)
{
  if (cond)
    foo();
  if(cond)
    bar();
}

// test reordering (clang) ////////////////////////////////////////
void foo();

void doit(int x, int y)
{
  if (x * y * 88 + 1234 < y*y)
  {
    if (x > 55)
    {
      foo();
    }
  }
}

// dead code removal ////////////////////////////
int sum(int* arr, int size)
{
  int t = 0;
  for(int i = 0; i < size; i+=2)
    t *= arr[i];
  
  return size+7;
}

// recursion removal //////////////////////////////
int fib(int x)
{
  if (x < 2)
    return 1;
 	else
      return fib(x-1) + fib(x-2);
}


int fac(int n)
{
  if (n < 2)
    return 1;
  else
    return n * fac(n-1);
}

// dead branch + inlining ///////////////////////////
#include <vector>
#include <boost/optional.hpp>

boost::optional<double> get_first(const std::vector<double>& v)
{
	if (v.size() == 0)
		return boost::none;
	else
		return v.at(0);
}

// noexcept impact ///////////////////////////////////////
#include <memory>

void foo(int&);

void bar() noexcept
{
  auto i = std::make_unique<int>(7);
  foo(*i);
}

// Copy elision ///////////////////////////////////
struct ExpensiveToCopy
{
  ExpensiveToCopy();
  ExpensiveToCopy(double val);
  ExpensiveToCopy(const ExpensiveToCopy&);
  
  ExpensiveToCopy& operator=(const ExpensiveToCopy&);
  
  void do_smthn();
};

ExpensiveToCopy get_instance()
{
  return ExpensiveToCopy(4.14);
}


void get_and_do()
{
  ExpensiveToCopy i = get_instance();  
  i.do_smthn();
}
// copy elisoon 2 /////////////////////////////////////
struct ExpensiveToCopy
{
  ExpensiveToCopy();
  ExpensiveToCopy(double val);
  ExpensiveToCopy(const ExpensiveToCopy&);
  
  ExpensiveToCopy& operator=(const ExpensiveToCopy&);
  
  void do_smthn();
};

ExpensiveToCopy return_by_val2(int y);

ExpensiveToCopy return_by_val(int y)
{
 ExpensiveToCopy e(8.9* y); 
  
  return e;
}

void use()
{
  ExpensiveToCopy i = return_by_val2(8);
}

// loop invariant ////////////////////////////////////

int fun(int x, int y)
{
  for(int i = 0; i < 10; i++)
  {
    if (y < 88) return 99;
    x++;
  }
  return x;
}
// unsgined int //////////////////////////////////////////
int foo(int a, unsigned int b)
{
  for(int i = 0; i < 10; i++)
  {
    if (b+i > b) return 6;
    a++;
  }
  return a;
}

// memcopy //////////////////////////////////////
#include <algorithm>

void copy_block3(char* buffer, unsigned off_a, unsigned off_b, unsigned len)
{
  std::copy(buffer+off_a, buffer+off_a+len, buffer+off_b);
}

void copy_block2(char* buffer, unsigned off_a, unsigned off_b, unsigned len)
{
	while(len > 0)
    {
      buffer[off_b] = buffer[off_a];
      ++off_b; ++off_a; --len;
    }
}

// memset + unsigned /////////////////////////////////////////////
void zero_array(float* P, int offset)
{
   for (int i = 0; i != 10000; ++i)
     P[i+offset] = 0.0f;
}


// double check /////////////////////////////
int get_val(int* buf, int offset)
{
  if (buf)
    return buf[offset];
  else
    return 0;
}

int sum(int* buf)
{
  if (buf == nullptr)
    return 0;
  
  return get_val(buf, 0) + get_val(buf, 1);
}


// null-pointer check + dereference /////////////////////////////
int super_expensive();

void set_val(int* buf, int val)
{
  int v = *buf;
  if (buf)
    *buf = val;
  else
    *buf = val + super_expensive();
}

// null-pointer check elision /////////////////////////////////////
struct Data {
  int a;
  void foo();
};

Data* get_data();


void act()
{
  Data* ptr = get_data();
  ptr->a = 7;
  
  if (ptr)
  {
    ptr->foo();
  }
}

// interesting one ////////////////////////////////////////
int foo(int i)
{
  int x[2];
  x[i] = 12;
  return x[i];
}

// undefined behaviour - /0 (see clang) ///////////////////////////////////
static int div(int a, int b)
{
  return a / b;
}

int res()
{
  int a = 0;
  for(int i = 0; i < 5; i++)
  {
    a += div(5, i);
  }
  return a;
}

// bound checking removal (clang vs gcc) ////////////////////////////////////
#include <vector>
#include <cassert>

std::vector<int> foo()
{
  std::vector<int> v;
  //v.reserve(2);
  
  v.push_back(44);
  v.push_back(77);
  
  return v;
}

// compare - loop simplification to memcmp ////////////////////////////////////////////
#include <algorithm>

bool cmp(char* a, char* b, int l)
{
  return std::equal(a, a+l, b);
}

bool cmp2(char* a, char* b, int l)
{
  return std::all_of(a, a+l, [&](char c) { return c==*b; b++; }); 
}

// Speculative devirtualization /////////////////////////////////
struct Class
{
  virtual int code() const { return 4; };
};


int get_code(const Class& c)
{
  return c.code();
}

// Devirtualization ////////////////////////////////////////
#include <iterator>

struct Shape { virtual int edges() const = 0; };

struct Triangle : Shape { int edges() const override { return 3; } };
struct Square : Shape { int edges() const override { return 4; } };
struct Hexagon : Shape { int edges() const override { return 6; } };

int calc()
{
  Shape* shapes[3];
  Triangle t; Square s; Hexagon h;
  shapes[0] = &t;
  shapes[1] = &s;
  shapes[2] = &h;
  
	int total = 0;
  for(Shape* s : shapes)
  {
    total += s->edges();
  }
  
  return total;
}


// uninitialized value //////////////////////////////////////////////
void foo();
void bar();

int get_x()
{
  int x;
  return x;
}

void act()
{
  int x;
  if (x != 7)
    foo();
  else
    bar();
}

// recursion + inlininkg + const prop + loop unrolling
#include <cstring>
#include <algorithm>

inline void serialize(char*) {} //terminator

template<typename T>
size_t copy_to_buffer(char* buf, const T& v)
{
  *reinterpret_cast<T*>(buf) = v;
  return sizeof(T);
}

inline size_t copy_to_buffer(char* buf, const char* s)
{
  size_t l = std::strlen(s);
  std::copy(s, s+l, buf);
  return l;
}

template<typename Arg, typename... Args>
void serialize(char* buf, const Arg& arg, const Args&... values)
{
  auto sz = copy_to_buffer(buf, arg);
  serialize(buf +  sz, values...);
}



void foo(char* buf)
{
  serialize(buf, 5, 33.3, 'c');
}

void bar(char* buf, const char* str)
{
  serialize(buf, 77, str);
}

void baz(char* buf)
{
  serialize(buf, "hello", 42);
}


