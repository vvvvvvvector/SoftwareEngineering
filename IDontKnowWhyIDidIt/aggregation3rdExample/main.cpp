#include <iostream>
#include <vector>

class TStudent
{
private:
    std::string studentName;
    int studentAge;

public:
    TStudent()
    {
        std::cout << "TStudent constructor\n";
    }

    ~TStudent()
    {
        std::cout << "TStudent destructor\n";
    }

    void setName(const std::string &name)
    {
        this->studentName = name;
    }

    std::string getName() const
    {
        return this->studentName;
    }

    void setAge(const int age)
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
private:
    std::vector<TStudent *> students;

public:
    void attach(TStudent *student)
    {
        students.push_back(student);
    }

    void detach()
    {
        students.pop_back();
        std::cout << "After removing element of vector students: " << (students.empty() ? "is empty\n" : "isn't empty\n");
    }

    void printData(int i)
    {
        std::cout << this->students[i]->getName() << '\t';
        std::cout << this->students[i]->getAge() << '\n';
    }

    void setData(int i, std::string name, int age)
    {
        this->students[i]->setName(name);
        this->students[i]->setAge(age);
    }
};

int main()
{
    TStudent *ptrStudent = new TStudent();
    TUniversity *ptrUniversity = new TUniversity();

    ptrUniversity->attach(ptrStudent);
    ptrUniversity->setData(0, "Wojtek", 24);
    ptrUniversity->printData(0);

    ptrUniversity->attach(ptrStudent);
    ptrUniversity->setData(1, "Jola", 19);
    ptrUniversity->printData(1);

    ptrUniversity->detach();
    ptrUniversity->detach();

    delete ptrStudent;
    delete ptrUniversity;

    return 0;
}