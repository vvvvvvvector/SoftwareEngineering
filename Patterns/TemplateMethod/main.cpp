#include <iostream>

class AbstractClass
{
public:
    void TemplateMethod()
    {
        std::cout << "i'm a template method\n";
        this->BaseOperation();
        this->RequariedOperation();
        this->AdditionalOperation();
    }

protected:
    void BaseOperation()
    {
        std::cout << "i'm base opertaion!\n";
    }

    virtual void RequariedOperation() const = 0;

    virtual void AdditionalOperation() const
    {
        std::cout << "additional operation default behaviour\n";
    }
};

class ConcreteClass1 : public AbstractClass
{
protected:
    void RequariedOperation() const override
    {
        std::cout << "requaried operation first implementation(ConcreteClass1)\n";
    }

    void AdditionalOperation() const override
    {
        std::cout << "additional operation first implementation(ConcreteClass1)\n";
    }
};

class ConcreteClass2 : public AbstractClass
{
protected:
    void RequariedOperation() const override
    {
        std::cout << "requaried operation second implementation(ConcreteClass2)\n";
    }
};

int main()
{
    ConcreteClass1 *class1 = new ConcreteClass1();

    class1->TemplateMethod();

    std::cout << '\n';

    ConcreteClass2 *class2 = new ConcreteClass2();

    class2->TemplateMethod();

    delete class1;
    delete class2;

    return 0;
}