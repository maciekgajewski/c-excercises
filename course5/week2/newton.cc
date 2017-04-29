#include <iostream>
#include <cmath>

// ARS 20170215
// Newtonś methon from http://www.school-for-champions.com/algebra/square_root_approx.htm

const float EPSILON = 1.0e-4;

float sqrt(float nr, float guess, int& iteration, long* stackptr)
{
	// Do some extra to determine the size of the stackframe per function call
	// first call to this function will pass a nullptr, so set the 'base' to the
	// address of the dummy after the first call

	// OBSERVATIONS: Memory grows 'down'.  Ech iteration is starting at an address
	// smaller than the previous one. Example:
/* 
anil@anil-VirtualBox:~/cc/week2$ ./newton 267
Estimated cumulative stackframe (0x7ffc32314d90-0x7ffc32314d30) = 12 in iter 2 for an average of 12 bytes per invocation.
Estimated cumulative stackframe (0x7ffc32314d90-0x7ffc32314cd0) = 24 in iter 3 for an average of 12 bytes per invocation.
Estimated cumulative stackframe (0x7ffc32314d90-0x7ffc32314c70) = 36 in iter 4 for an average of 12 bytes per invocation.
*/

	long dummy= 0;
	if (stackptr != nullptr)
	{
		long diff = stackptr - &dummy;
		std::cout << "Estimated cumulative stackframe ("<< stackptr << "-" << &dummy << ") = "<< diff << " in iter "<< iteration << " for an average of " << diff/(iteration-1) << " bytes per invocation."<<  std::endl;

	}
	else
	{	
		stackptr = &dummy;
	}

	// Do the actual sqrt calculation
	if  (std::fabs(nr - guess*guess) < EPSILON)
	{
		return guess;
	}
	else
	{
		auto new_guess = 0.5*(nr/guess + guess);
		iteration++;
		return sqrt(nr, new_guess, iteration, stackptr);
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "usage: " << argv[0] << " <nr>"<< std::endl;
		exit(0);
	}

	auto nr = std::stof(argv[1])	;
	int iteration = 1;

	std::cout << "sqrt("<< nr << ")=" << sqrt((float)nr,nr/2.0, iteration, nullptr) << std::endl;
	std::cout << "calcluated in " << iteration << " iterations" << std::endl;
	return 0;
}
