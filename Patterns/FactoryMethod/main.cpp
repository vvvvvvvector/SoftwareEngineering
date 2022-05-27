#include <iostream>
#include <list>
#include <ctime>

// Product interface
class NumbersList
{
public:
    virtual ~NumbersList(){};
    virtual void TraverseList() = 0;
};

// ConcreteProduct 1
class IntegersList : public NumbersList
{
private:
    std::list<int> numbers;

public:
    void AddNumber(int num)
    {
        this->numbers.push_back(num);
    }

    void TraverseList() override
    {
        for (auto i = this->numbers.begin(); i != this->numbers.end(); i++)
        {
            std::cout << (*i) << ' ';
        }
        std::cout << '\n';
    }
};

// ConcreteProduct 2
class DoublesList : public NumbersList
{
private:
    std::list<double> numbers;

public:
    void AddNumber(double num)
    {
        this->numbers.push_back(num);
    }

    void TraverseList() override
    {
        for (auto i = this->numbers.begin(); i != this->numbers.end(); i++)
        {
            std::cout << (*i) << ' ';
        }
        std::cout << '\n';
    }
};

// Creator
class ListsCreator
{
public:
    virtual ~ListsCreator(){};
    virtual NumbersList *CreateList(int list_size) const = 0;

    void GenerateNumbers(int list_size)
    {
        NumbersList *list = this->CreateList(list_size);

        list->TraverseList();

        delete list;
    }
};

// Concrete Creator 1
class RandomIntegersList : public ListsCreator
{
public:
    NumbersList *CreateList(int list_size) const override
    {
        IntegersList *list = new IntegersList();
        for (int i = 0; i < list_size; i++)
        {
            list->AddNumber(rand() % 101);
        }
        return list;
    }
};

// Concrete Creator 2
class SequentialIntegersList : public ListsCreator
{
public:
    NumbersList *CreateList(int list_size) const override
    {
        IntegersList *list = new IntegersList();
        for (int i = 0; i < list_size; i++)
        {
            list->AddNumber(i + 1);
        }
        return list;
    }
};

// Concrete Creator 3
class RandomDoublesList : public ListsCreator
{
public:
    NumbersList *CreateList(int list_size) const override
    {
        DoublesList *list = new DoublesList();
        for (int i = 0; i < list_size; i++)
        {
            list->AddNumber(-5 + ((double)rand() / RAND_MAX) * (5 - (-5)));
        }
        return list;
    }
};

int main()
{
    srand(time(nullptr));

    ListsCreator *random_integers = new RandomIntegersList();
    ListsCreator *sequential_integers = new SequentialIntegersList();
    ListsCreator *random_doubles = new RandomDoublesList();

    random_integers->GenerateNumbers(4);
    sequential_integers->GenerateNumbers(10);
    random_doubles->GenerateNumbers(3);

    delete random_integers;
    delete sequential_integers;
    delete random_doubles;

    return 0;
}