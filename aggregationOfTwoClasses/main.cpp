#include <iostream>

class TStudent
{
    std::string studentName;
    int studentAge;

public:
    void setName(const std::string &name)
    {
        this->studentName = name;
    }

    std::string getName() const
    {
        return this->studentName;
    }

    void setAge(int age)
    {
        this->studentAge = age;
    }

    int getAge() const
    {
        return this->studentAge;
    }
};

class TUniversity
{
    TStudent student; // aggregation TStudent class with TUniversity class
    std::string name;

public:
    TUniversity(const std::string &name)
    {
        this->name = name;
        std::cout << "University name: " << this->name << '\n';
    }

    void printData()
    {
        std::cout << "Student name: " << student.getName() << '\n';
        std::cout << "Student age: " << student.getAge() << '\n';
    }

    void setDate(std::string name, int age)
    {
        this->student.setName(name);
        this->student.setAge(age);
    }
};

int main()
{
    TUniversity *ptrUni = new TUniversity("UMCS");

    ptrUni->setDate("Jan Kowalski", 21);

    ptrUni->printData();

    delete ptrUni;

    return 0;
}