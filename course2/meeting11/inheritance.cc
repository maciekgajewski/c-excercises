#include <iostream>
#include <string>

class Person
{
public:

    virtual ~Person() = default;
    
    std::string firstName;
    std::string lastName;
    
    virtual void ToStream(std::ostream& s) const
    {
        s << "f: "<<firstName << ", l:"<<lastName;
    }
};

class Employee : Person
{
public:
    std::string role;
    
    void ToStream(std::ostream& s) const
    {
        Person::ToStream(s);
        s << ", r: " << role;
    }
    
};

void PrintPerson(const Person& p)
{
    p.ToStream(std::cout);
    std::cout << std::endl;
    
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
    
    PrintPerson(maciek);
    PrintPerson(mat);
 
    Employee* e = new Employee;
    e->role = "some text";
    
    Person* p = e;
    
    delete p;
    
    
    std::cout << "sizeof(maciek) = " << sizeof(maciek) << std::endl;
}