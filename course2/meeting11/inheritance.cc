#include <iostream>
#include <string>

class IStreamable
{
public:
    virtual void ToStream(std::ostream& s) const = 0;
    
};

class Person : public IStreamable
{
public:

    virtual ~Person() = default;
    
    std::string firstName;
    std::string lastName;
    
    void ToStream(std::ostream& s) const
    {
        s << "f: "<<firstName << ", l:"<<lastName;
    }
};

class Employee : public Person
{
public:
    std::string role;
    
    void ToStream(std::ostream& s) const override final
    {
        Person::ToStream(s);
        s << ", r: " << role;
    }
    
};

void PrintPerson(const IStreamable& p)
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
 
    Person* maciek_p = &maciek;
    Person* mat_p = &mat;
    
    Employee* maciek_ep = dynamic_cast<Employee*>(maciek_p);
    Employee* mat_ep = dynamic_cast<Employee*>(mat_p);
    
    std::cout << "maciek_ep = " << maciek_ep << std::endl;
    std::cout << "mat_ep = " << mat_ep << std::endl;
    
    std::cout << "sizeof(maciek) = " << sizeof(maciek) << std::endl;
}