#include <iostream>
#include <string>

class Record
{
    int id;
};

class Person
{
public:
    
    std::string firstName;
    std::string lastName;
};

class Employee : public Record, public Person
{
public:
    std::string role;
};

void PrintPerson(const Person& p)
{
    std::cout << "first: " << p.firstName << ", last: "<< p.lastName << std::endl;
}

int main()
{
    
    Employee maciek;
    maciek.firstName = "Maciek";
    maciek.lastName = "G";
    maciek.role = "Dev";
 
    Person mat;
    mat.firstName = "Matthijs";
    mat.lastName = "S";
    
 
    Employee* ep = &maciek;
    Person* pp = ep;
    Record* rp = &maciek;
    
    Employee* ep2 = dynamic_cast<Employee*>(pp);

    std::cout << "ep = " << ep << std::endl;
    std::cout << "pp = " << pp << std::endl;
    std::cout << "rp = " << rp << std::endl;
    std::cout << "ep2= " << ep2 << std::endl;
    
    PrintPerson(maciek);
    PrintPerson(mat);
    
    
    
    std::cout << "sizeof(maciek) = " << sizeof(maciek) << std::endl;
}