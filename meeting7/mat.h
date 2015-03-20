#include "log.h"

class Calculator
{
public:
    double square(double);
    
    double sum(double a, double b)
    {
        Logger l;
        l.log("Inside Calculator::sum");
        return a+b;
        
    }
    
    double max(double a, double b);
};

