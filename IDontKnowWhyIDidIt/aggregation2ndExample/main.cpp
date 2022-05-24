#include <iostream>
#include <vector>

class TStudent
{
public:
    TStudent()
    {
        std::cout << "TStudent constructor\n";
    }

    ~TStudent()
    {
        std::cout << "TStudent destructor\n";
    }
};

class TUniversity
{
private:
    std::vector<TStudent *> students;
    std::vector<TStudent *>::iterator it;

public:
    void attach()
    {
        TStudent *students = new TStudent[5];
        this->students.push_back(students);
    }

    void detach()
    {
        for (it = this->students.begin(); it != this->students.end(); ++it)
        {
            delete[] * it;
        }
    }
};

int main()
{
    TUniversity *ptrUniversity = new TUniversity();

    ptrUniversity->attach();
    ptrUniversity->detach();

    delete ptrUniversity;

    return 0;
}