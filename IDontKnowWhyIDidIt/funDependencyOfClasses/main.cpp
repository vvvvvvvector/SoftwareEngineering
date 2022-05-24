#include <iostream>

class A // independent class
{
private:
    int i;

public:
    A()
    {
        this->i = 10;
    };

    void funA()
    {
        this->i *= 10;
        std::cout << this->i << '\n';
    }
};

class B // dependent class
{
private:
    // attribute list

public:
    void funB(A *ptrClassA)
    {
        ptrClassA->funA();
    }
};

int main()
{
    A objClassA;
    B *ptrClassB;

    ptrClassB->funB(&objClassA);

    return 0;
}